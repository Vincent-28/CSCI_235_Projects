#include "FileLoader.hpp"
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>

/**
 * Loads a text file from disk into a TextFile object.
 *
 * @param str_path_to_file A const reference to a STRING representing the path to the text file.
 * @return A TextFile object containing the file's name and contents.
 * @throws std::invalid_argument if:
 *  1. The file does not exist.
 *  2. The file extension is not ".txt".
 * @post
 * - All boolean File members are set to true
 * - The File filename is explicitly set to the name of the file only -- no directory
 *   information included.
 *   (e.g. "homework/my_file.txt" has a filename of "my_file.txt")
 * - The TextFile contents is set to the text content of the specified file
 *
 * @see Useful Links:
 * 1. C++ Exceptions: https://en.cppreference.com/w/cpp/header/stdexcept.html
 * 2. The std::filesystem::path (from <filesystem> header) type: https://en.cppreference.com/w/cpp/filesystem/path.html
 *    - Contains how to get the extension & filename from the file system path
 *    - How to create a path object: https://stackoverflow.com/questions/43114174/convert-a-string-to-std-filesystem-path
 * 3. Check if file Exists: https://en.cppreference.com/w/cpp/filesystem/exists.html
 * 4. Input File Streams (refresher from 135): https://www.w3schools.com/cpp/ref_fstream_ifstream.asp
 */

/**
 * Loads an image file from disk into an ImageFile object.
 *
 * Supported formats: PNG (.png) and JPEG (.jpg).
 *
 * @param str_path_to_file A const reference to a STRING representing the path to the image file.
 * @return An ImageFile object containing the file's name and pixel data buffer
 * @throws std::invalid_argument if:
 *  1. The file does not exist.
 *  2. The file extension is not ".png" or ".jpg".
 * @post
 * - All boolean File members are set to true
 * - All dynamic memory (that is, pointers) is released (so READ the documentation in stb file please)
 * - The filename of the File is explicitly set to the name of the file only -- no directory
 *   information included.
 *
 * @see stb_image.h Read the documentation section
 * - You will have to reshape the 1D array of RGB channel values
 *   into a 2D array of Pixel structs
 */

namespace fs = std::filesystem;

TextFile FileLoader::loadTextFile(const std::string& str_path_to_file) {//function that loads a text file and turns it into a TextFile object
    fs::path objPath(str_path_to_file);//create a filesystem path object using the file path we were given

    if (!fs::exists(objPath)) {
        throw std::invalid_argument("File does not exist: " + str_path_to_file);
    }//if the file doesn’t exist, throw an error

    const std::string ext = objPath.extension().string();//get the extension of the file as a string
    if (ext != ".txt") {
        throw std::invalid_argument("Invalid extension: " + ext);
    }//if the file extension isn’t .txt, throw an error since this function only loads text files

    std::ifstream in(objPath, std::ios::in);//open the file for reading
    if (!in.is_open()) {
        throw std::invalid_argument("File cannot be opened: " + str_path_to_file);
    }//if the file couldn’t be opened, throw an error

    std::ostringstream buffer;//create a stream to store everything from the file
    buffer << in.rdbuf();//read the entire contents of the file into the buffer              
    const std::string contents = buffer.str();//convert the buffer into a normal string

    const std::string base_filename = objPath.filename().string();//get just the filename (without any folder path)

    return TextFile(base_filename, contents);//create and return a TextFile object with the name and contents
}

ImageFile FileLoader::loadImageFile(const std::string& str_path_to_file) {//function that loads an image file and turns it into an ImageFile object
    fs::path objPath(str_path_to_file);//create a filesystem path object from the given path
    if(!fs::exists(objPath)) {
        throw std::invalid_argument("File does not exist: " + str_path_to_file);
    }//if the image file doesn’t exist, throw an error

    const std::string ext = objPath.extension().string();//get the extension of the file (for example .png or .jpg)
    if (ext != ".png" && ext != ".jpg") {                          
        throw std::invalid_argument("Invalid image extension: " + ext);
    }//if the extension isn’t .png or .jpg, throw an error since those are the only supported types

    const std::string base_filename = objPath.filename().string();//get just the filename part without folders

    int width = 0;//store the width of the image
    int height = 0;//store the height of the image
    int originalChannels = 0;//store the number of color channels in the image

    //load the image data using stb_image and get its width, height, and color channels
    unsigned char* data = stbi_load(str_path_to_file.c_str(), &width, &height, &originalChannels, 3);

    if (data == nullptr) {
        throw std::runtime_error("stb_image failed to load.");
    }//if stb_image couldn’t load the image, throw an error

    if (width <= 0 || height <= 0) {
        stbi_image_free(data);
        throw std::runtime_error("Invalid image dimensions.");
    }//if the image width or height is invalid, free the memory and throw an error

    std::vector<std::vector<Pixel>> pixels;//create a 2D vector to store the pixels
    pixels.resize(static_cast<std::size_t>(height), std::vector<Pixel>(static_cast<std::size_t>(width)));
    //resize the vector so it matches the image’s height and width

    //go through every pixel in the image
    for (int i = 0; i < height; i++) {//loop through each row
        for (int j = 0; j < width; j++) {//loop through each column
            const int idx = (i * width + j) * 3;//find where this pixel starts in the 1D image data array
            const int r = data[idx + 0];//get the red value
            const int g = data[idx + 1];//get the green value
            const int b = data[idx + 2];//get the blue value
            pixels[i][j] = Pixel{r, g, b};//store that RGB color inside the 2D pixels grid
    }
}

    stbi_image_free(data);//free the memory that stb_image used after we finish reading the image

    ImageFile img(base_filename, pixels, true, true);//create an ImageFile object with the image name and pixel data

    return img;//return the created ImageFile
}