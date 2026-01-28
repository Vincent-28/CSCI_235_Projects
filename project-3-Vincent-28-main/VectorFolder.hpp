#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include <stdexcept>

class File;

class VectorFolder {
private:
    std::vector<File> files_;

    size_t indexOf(const std::string& filename) const;

public:
    VectorFolder();

    size_t getFileCount() const;

    File findFile(const std::string& filename) const;

    bool addFile(const File& file);

    bool removeFile(const std::string& filename);

    std::vector<File> getFiles() const;
};