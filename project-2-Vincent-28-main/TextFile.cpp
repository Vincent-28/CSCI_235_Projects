#include "TextFile.hpp"
#include <iostream>
#include <sstream>

/**
 * Constructs a new TextFile object.
 *
 * @pre For simplicity, we assume that the filename extension is that of a text file -- you need not validate it.
 *
 * @param filename  A const reference to a string representing the filename of the text file.
 * @param content   A const reference to a string representing the initial file contents (defaults to an empty string if omitted).
 * @param readable  A boolean indicating whether the file is readable (defaults to true if omitted).
 * @param writable  A boolean indicating whether the file is writable (defaults to true if omitted).
 *
 * @post
 * 1. The filename and permissions are initialized via the base File constructor.
 * 2. The file contents are set to the provided string, or remain empty if none is provided.
 *
 * @note You should be initializing the base class explicitly (refer to lecture)
 */

/**
 * Retrieves the current contents of the text file.
 * @return A string containing the text file's contents.
 */

/**
 * Updates the content of the text file.
 *
 * @param newContent A const reference to a string representing the new file contents.
 * @post
 * 1. The content_ member variable is updated to match the provided string.
 * 2. The last_modified_timestamp_ of the underlying File is updated to the current time
 * specified by Clock::now.
 *
 * @note Hint: You will need to modify `File` (ie. the base class) to allow you to actually update the last modified timestamp.
 */

/**
 * Generates a formatted string representation of the text file.
 *
 * @return A string containing the file's name, permissions, last modified timestamp,
 *         and contents, or "(none)" if the contents are empty.
 */

TextFile::TextFile(const std::string& filename, const std::string& content, const bool& readable, const bool& writable) : File(filename, readable, writable), content_(content) {

}//constructor for the TextFile class

std::string TextFile::getContent() const { //function that returns the content of the text file
    return content_;//return whatever is stored in content_
}

void TextFile::setContent(const std::string& newContent) {//function that sets or changes the content of the text file
    content_ = newContent;//replace the old content with the new one
    updateLastModified();//call the base class function to update the last modified time whenever content changes
}

std::string TextFile::toString() const {//function that prints out all the information about the text file in a readable way
    std::ostringstream out;//create an output string stream to format text

    std::cout << "Filename: " << getFilename() << "\n";

    std::cout << "Readable: " << (isReadable() ? "Yes" : "No") << "\n";
    std::cout << "Writable: " << (isWritable() ? "Yes" : "No") << "\n";

    if (content_.empty()) {
        std::cout << "Contents: (none)\n";
    } else {
        std::cout << "Contents: " << content_ << "\n";
    }
    return out.str();
}

