#include "ImageFile.hpp"
#include <sstream>
#include <iostream>
#include <string>

/**
 * A 2D vector of Pixel structs
 * The pixel data is stored in a 2D vector, where pixels_[row][col] corresponds to
 * the pixel at the given row and column of the image.
 *
 * pixels_[0][0] should be the top-left of the image
 * pixels_[YOUR_IMAGE_HEIGHT - 1][YOUR_IMAGE_WIDTH - 1] should be the bottom-right of the image
 */

/**
 * Constructs a new ImageFile object.
 *
 * The pixel data is stored in a 2D vector, where pixels[row][col] corresponds to
 * the pixel at the given row and column of the image.
 *
 * @pre Assume that the image ends with a valid image extension (i.e. you do not need to validate it).
 *
 * @param filename A const reference to a string representing the filename of the image.
 * @param pixels   A const reference to a 2D vector of Pixel objects representing the image's pixel data.
 *                 Defaults to a grid of 20(width) x 10(height) pixels initialized to black (0,0,0).
 * @param readable A boolean indicating whether the file is readable (defaults to true if omitted).
 * @param writable A boolean indicating whether the file is writable (defaults to true if omitted).
 *
 * @post
 * 1. The filename and permissions are initialized via the base File constructor.
 * 2. The pixel buffer is set to the provided vector, or initialized to the default size with all black pixels if...
 *  - The parameter is omitted (ie. as a default value).
 *  - Or the pixel array's rows are not all the same length.
 *
 * @note It IS allowed to set pixels to an empty 2D vector!
 */

/**
 * Updates the pixel buffer of the image if given a valid pixel array; otherwise, returns false.
 *
 * @param pixels A const reference to a 2D vector of Pixel objects representing the new image data.
 * @returns True if the operation was successful, false otherwise.
 * @post
 * 1. If the new pixel array's rows are not all the same length, NO member is updated and false is returned.
 * 2. Otherwise, the pixels_ member variable is updated to match the provided 2D vector.
 *    and the last_modified_timestamp_ of the underlying File is updated to the current time
 *    specified by the Clock class
 *
 * @note It IS allowed to set pixels to an empty 2D vector!
 */

/**
 * Retrieves the current pixel buffer of the image.
 *
 * @return A 2D vector of Pixel objects, where pixels[row][col] corresponds to the pixel at
 *         the specified row and column.
 */

/**
 * Retrieves the height (number of rows) of the image.
 * @return An integer representing the total number of rows in the pixel buffer.
 */

/**
 * Retrieves the width (number of columns) of the image.
 * @return An integer representing the total number of columns in the pixel buffer.
 */

/**
 * Generates a string representation of the image file.
 *
 * @return A string containing the file's name, permissions, last modified timestamp,
 *         and image dimensions (width x height).
 */


bool ImageFile::isRectangular_(const std::vector<std::vector<Pixel>>& data) {//function that checks if the 2D vector of pixels forms a rectangle (each row must be the same length)
    if (data.empty()) {
        return true;//if the vector is empty, just return true since there's nothing to check
    }
    const std::size_t width = data.front().size();//get the width of the first row (how many pixels in that row)

    for (const auto& row : data) {//go through each row in the pixel grid
        if (row.size() != width) {//if any row has a different number of pixels than the first
            return false;//it means the image isn't rectangular, so return false
        }
    }
    return true;//if every row matched in size, return true because it's rectangular
}

std::vector<std::vector<Pixel>> ImageFile::makeDefaultBlackGrid_() { //function that creates a default 10x20 black image grid (used when something goes wrong)
    const int height = 10;//set the height (number of rows)
    const int width = 20;//set the width (number of columns)
    return std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width, Pixel{0, 0, 0}));//create a 2D vector that’s 10 rows by 20 columns filled with black pixels (RGB = 0,0,0)
}

ImageFile::ImageFile(const std::string& filename, const std::vector<std::vector<Pixel>>& pixels, const bool& readable, const bool& writable) : File(filename, readable, writable), pixels_() { //constructor for the ImageFile class that sets up the filename, readability, writability, and pixel data //call the File constructor and set pixels_ to empty for now
    if (isRectangular_(pixels)) {//check if the pixel grid passed in is rectangular
        pixels_ = pixels;//if yes, store those pixels
    }
    else {
        pixels_ = makeDefaultBlackGrid_();//if not rectangular, create a default black grid instead
    }
}

std::vector<std::vector<Pixel>> ImageFile::getPixels() const {//function that returns all the pixels (the 2D grid of colors)
    return pixels_;//return the image’s pixel data
}

bool ImageFile::setPixels(const std::vector<std::vector<Pixel>>& pixels) {//function that changes the pixel grid to a new one
    if (!isRectangular_(pixels)) {//check if the new grid is rectangular
        return false;//if not, do nothing and return false
    }
    pixels_ = pixels; //otherwise set the new pixel grid
    updateLastModified();//update the file’s “last modified” timestamp since content changed
    return true;//return true to show it worked
}

int ImageFile::getHeight() const {//function that returns the height of the image (how many rows of pixels)
    return static_cast<int>(pixels_.size());//the number of rows in the 2D pixel grid
}

int ImageFile::getWidth() const {//function that returns the width of the image (how many columns of pixels)
    if (pixels_.empty()) {//if there are no rows at all
        return 0;//return 0 for width
    }
    return static_cast<int>(pixels_.front().size());//otherwise, width is how many pixels are in the first row
}

/**
 * Generates a string representation of the image file.
 *
 * @return A string containing the file's name, permissions, last modified timestamp,
 *         and image dimensions (width x height).
 */
std::string ImageFile::toString() const {//function that prints all the info about the image in a readable way
    // SAFE: No calls to File::toString() or Pixel::toString()
    std::ostringstream ss;//create a string stream to hold text
    ss << "Filename: " << getFilename() << "\n";//print the image file name
    ss << "Readable: " << (isReadable() ? "Yes" : "No") << "\n";//print if the file can be read
    ss << "Writable: " << (isWritable() ? "Yes" : "No") << "\n";//print if the file can be written to
    ss << "Resolution: " << getWidth() << "x" << getHeight() << "\n";//print image width and height
    return ss.str();//return the formatted text as a string
}