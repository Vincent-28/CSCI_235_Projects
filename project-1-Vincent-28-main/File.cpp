/*
Name: Vincent Sang
Date: September 9th, 2025
*/

/*
This file defines the File class.
It stores a filename and two permissions (read / write),
and keeps track of when the file was last changed.

What this class does:
  - builds File objects (default and custom)
  - lets you check and change read/write permissions
  - lets you get/change the filename (with simple rules)
  - tracks a “last modified” time whenever something changes
*/

#include "File.hpp"
#include "FileUtils.hpp"
#include <string>
#include <ctime> 

/*
  Parameterized Constructor
  Builds a File with an initial name and permissions.

  Rules for the filename parameter:
    1) if empty OR contains whitespace -> use default name
    2) if it has no '.' at all        -> append ".txt"
    3) if it ends with '.'             -> append "txt" (no extra dot)
    4) otherwise use the given name as-is

filename     the desired starting filename
isReadable   initial read permission
isWritable   initial write permission
none
filename_ set using the rules above
        readable_/writable_ set from the parameters
        last_modified_ and last_modified_timestamp_ set to “now”
*/

/*
this code builds a File that behaves a bit like a real one, making sure names follow simple rules, keeping track of permissions, and remembering the last time it was updated.
*/

File::File() : 
    filename_("New_Text_Document.txt"), // set default filename
    readable_(true), // set default read permission
    writable_(true), // set default write permission
    last_modified_(std::time(nullptr)), // set legacy time_t timestamp (right now)
    last_modified_timestamp_(cr::system_clock::now())// set chrono timestamp (right now)
    {}// nothing else to do in the body

File::File(const std::string& filename, const bool& isReadable, const bool& isWritable) : readable_(isReadable), writable_(isWritable), last_modified_(std::time(nullptr)), last_modified_timestamp_(cr::system_clock::now()) {
    const std::string defaultString = "New_Text_Document.txt";

    if (FileUtils::hasWhitespaces(filename) || filename.empty()) {
        filename_ = defaultString;// rule 1: empty or has spaces -> default name
        return;
    }
    
    if (filename.find('.') == std::string::npos) {
        filename_ = filename + ".txt";// rule 2: no dot anywhere -> add ".txt"
        return;
    }

    if (FileUtils::findFileExtension(filename)[FileUtils::findFileExtension(filename).size() -1] == '.') { //this checks if the last character is a "."
        filename_ = filename + "txt";// rule 3: ends with '.' -> add "txt" (no extra dot)
        return;
    }

    filename_ = filename;// rule 4: otherwise, keep the provided name

}

bool File::isReadable() const {
    return readable_;// just give back the flag
}

void File::setReadable(const bool& new_permission) {
    readable_ = new_permission;// change the flag
    last_modified_timestamp_ = cr::system_clock::now();// record the change time
}

bool File::isWritable() const {
    return writable_;// just give back the flag
}

void File::setWritable(const bool& new_permission) {
    writable_ = new_permission;// change the flag
    last_modified_timestamp_ = cr::system_clock::now();// record the change time
}

std::string File::getFilename() const {
    return filename_; // return a copy of the name
}

bool File::setFilename(const std::string& filename) {
    if(FileUtils::hasWhitespaces(filename) || filename.empty()) {
        return false;// rule 1: invalid new name
    }
    
    const std::string newFile1 = FileUtils::findFileExtension(filename_);
    const std::string newFile2 = FileUtils::findFileExtension(filename);
    if (newFile1 != newFile2) {
        return false;// rule 2: extensions don’t match -> reject
    }

    filename_ = filename;// okay to change the name now

    last_modified_ = std::time(nullptr);// update legacy timestamp
    last_modified_timestamp_ = cr::system_clock::now();// update chrono timestamp
    return true;// tell the caller it worked
}

timestamp File::getLastModified() const {
    return last_modified_timestamp_;// return the stored time point
}


