#include <string>
#include "File.hpp"
#include "TextFile.hpp"
#include "ImageFile.hpp"
#include "stb_image.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <typeinfo>

int main() {
    try {
        TextFile tf = FileLoader::loadTextFile("sample_text_project2.txt");
        std::cout << "[TEXT] filename = " << tf.getFilename() << "\n";
        std::cout << "[TEXT] readable = " << (tf.isReadable() ? "true" : "false") << "\n";
        std::cout << "[TEXT] writable = " << (tf.isWritable() ? "true" : "false") << "\n";
        std::cout << "[TEXT] content  = " << tf.getContent() << "\n";

        ImageFile img = FileLoader::loadImageFile("dog.png");
        std::cout << "[IMG]  filename = " << img.getFilename() << "\n";
        std::cout << "[IMG]  readable = " << (img.isReadable() ? "true" : "false") << "\n";
        std::cout << "[IMG]  writable = " << (img.isWritable() ? "true" : "false") << "\n";
        std::cout << "[IMG]  width x height = " << img.getWidth() << " x " << img.getHeight() << "\n";
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << "\n";
        return 2;
    } catch (const std::runtime_error& re) {
        std::cerr << "Runtime error: " << re.what() << "\n";
        return 3;
    }
    return 0;
}