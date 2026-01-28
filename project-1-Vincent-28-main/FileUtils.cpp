/*
Name: Vincent Sang
Date: September 9th, 2025
*/

/*
This file contains helper functions inside the FileUtils namespace.
They make it easier to handle common file-related tasks, like:
   - Converting timestamps into readable strings
   - Checking for spaces in filenames
   - Taking the file extension
 These utilities are not part of a class. Instead, we group them into the FileUtils namespace to keep things neat and organized.
*/

#include "FileUtils.hpp"
#include <algorithm>

/*
One function can take a computer timestamp (which looks like a random number) and turn it into a nice human-readable date and time. 
Another checks if a filename has spaces in it, which usually aren’t allowed. And another one finds the file’s extension (like .txt or .jpg) by looking for the last dot in the name.
*/

std::string FileUtils::timestampToString(timestamp time_point)
{
    std::time_t tt = cr::system_clock::to_time_t(time_point);
    std::tm streamable_time = *std::localtime(&tt);

    std::stringstream ss;
    ss << std::put_time(&streamable_time, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// YOUR CODE BELOW HERE -------

//Task 1

std::string FileUtils::findFileExtension (const std::string& filename) {
    if (filename.empty()) {
        return "";
    } //this if statement first checks if filename is empty, if it is, then it will automatically return an empty string
    std::string fileExtension = ""; //this creates an empty string called fileExtension
    for (int i = filename.size() -1; i >= 0; i--) { //this for loop loops through the filename starting from the back and going in reverse
        if (filename[i] == '.') { //if the filename reaches a period (aka the last period in filename)
            fileExtension += '.'; //a period will be added to fileExtension
            std::reverse(fileExtension.begin(), fileExtension.end()); //every character that was added to fileextension from below, will be reversed so that it will be in the correct order since we were looping backwards.
            return fileExtension; //return fileExtension string
        }
        fileExtension += filename[i];                                  //everytime the loop doesnt see a period, last character will be added to file extension
    } 
    return ""; //this function is set up so that it will return an empty string if the filename is empty. If the filename only ends in a period, it will return a period. 
}

bool FileUtils::hasWhitespaces (const std::string& filename) {
    for (unsigned char c : filename) {
        if (std::isspace(c) != 0) {//this if statement checks if a character in filename has a space in it. If there is a character that has a space, it will automatically return true. 
            return true;
        }
    }
    return false; //if it doesnt find a space, it wil return false
}