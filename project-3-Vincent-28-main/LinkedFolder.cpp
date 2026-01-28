#include "LinkedFolder.hpp"
#include "File.hpp"

static std::string fileNameOf(const File& f) { //helper function that returns the name of a File object
    return f.getFilename();
}

/**
 * @brief Finds the index of a file with the given filename.
 * @param filename The name of the file to search for.
 *
 * @return The zero-based index of the file if found;
 * otherwise, returns the size of the internal LinkedList
 * (i.e. an index which is out of bounds of the actual LinkedList).
 */
size_t LinkedFolder::indexOf(const std::string& filename) const{
    const size_t name = files_.size();            
    for (size_t i = 0; i < name; i++) {         
        if (fileNameOf(files_.at(i)) == filename) { 
            return i;                         
        }
    }
    return name; 
}

size_t LinkedFolder::getFileCount() const{ //Gets the total number of files currently in the folder.
    return files_.size(); //The count of files as a size_t.
}

File LinkedFolder::findFile(const std::string& filename) const { //Searches for a file by its name.
    size_t index = indexOf(filename); //use the helper function indexOf to get the index of the filename
    if (index == files_.size()) { //in the function indexOf, we return files_.size() if the file is not found        
        throw std::runtime_error("File not found"); //so when the file is not found, we throw 
    }
    return files_.at(index); //in the case that a file is found (not the size fo the file) we return the file whose filename matches exactly, within the folder's files               
}

bool LinkedFolder::addFile(const File& file) { //Adds a new file to the folder.
    const std::string& name = fileNameOf(file);   
    if (indexOf(name) != files_.size()) { //if the index of the name of the file is not equal to the file size, that means it is already found in the filename        
        return false; //return false because there is a file that already exists with the same name                            
    } //we want the file to return the size of the file because that would mean that after doing indexOf, we did not find a file with the same name meaning we can now add it
    files_.push_back(file); //add the file using push_back               
    return true; //return true since we added the file                               
}

bool LinkedFolder::removeFile(const std::string& filename) { //Removes a file from the folder by its name.
    const size_t index = indexOf(filename); //we get the index of the file we want to remove          
    if (index == files_.size()) { //if the index is the file size, that means it was not found when we do indexOf so we return false                 
        return false;                            
    }
    files_.erase(index);                           
    return true;                                
}

LinkedList<File> LinkedFolder::getFiles() const{ //Access the underlying files vector
    return files_; //A vector of File objects representing the files in the VectorFolder
}

