#pragma once

#include <string>
#include <cstddef>
#include <stdexcept>
#include "LinkedList.hpp"

class File;

class LinkedFolder {
private:
    LinkedList<File> files_;

    size_t indexOf(const std::string& filename) const;

public:
    LinkedFolder() = default;

    size_t getFileCount() const;

    File findFile(const std::string& filename) const;

    bool addFile(const File& file);

    bool removeFile(const std::string& filename);

    LinkedList<File> getFiles() const;

};