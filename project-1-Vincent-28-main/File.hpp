#ifndef FILE_HPP
#define FILE_HPP

#include "FileUtils.hpp"
#include <string>
#include <ctime>

/*
This is the header file for the File class.
It contains the *interface* — the declarations of the class,
its data members, and the functions you can call on it.

What this class represents:
  - A "file" object with a name, read/write permissions,
    and a record of the last time it was modified.

What this file does:
  - Declares the File class (data members are private)
  - Declares constructors (default and parameterized)
  - Declares getter and setter methods for filename and permissions
  - Declares a getter for the last modified timestamp
*/

class File {
private: 
    std::string filename_;// stores the name of the file
    bool readable_;// true if file is readable
    bool writable_;// true if file is writable
    std::time_t last_modified_;// legacy timestamp (time_t)
    timestamp last_modified_timestamp_;// chrono timestamp (modern C++)
public:
    
    File();

    /*
    Parameterized constructor
    @param filename   desired starting filename
    @param isReadable initial read permission (default true)
    @param isWritable initial write permission (default true)

    @post filename_ follows these rules:
          1) empty or contains whitespace -> default name
          2) no '.' in filename -> append ".txt"
          3) ends with '.' -> append "txt"
          4) otherwise keep the given name
          readable_ and writable_ set to given booleans
          timestamps set to current time
    */

    File(const std::string& filename, const bool& isReadable = true, const bool& isWritable = true);

    bool isReadable() const;/*
    isReadable
    @return true if the file can be read, false otherwise
    @post does not change the object
    */

    void setReadable(const bool& new_permission);/*
    setReadable
    @param new_permission the new read permission
    @post readable_ is updated to new_permission
          last_modified_timestamp_ is updated to current time
    */

    bool isWritable() const;/*
    isWritable
    @return true if the file can be written to, false otherwise
    @post does not change the object
    */

    void setWritable(const bool& new_permission);/*
    setWritable
    @param new_permission the new write permission
    @post writable_ is updated to new_permission
          last_modified_timestamp_ is updated to current time
    */

    std::string getFilename() const;/*
    getFilename
    @return the current filename
    @post does not change the object
    */

    bool setFilename(const std::string& filename);
    /*
    setFilename
    @param filename the new filename to try
    @return true if update succeeded, false if failed

    @fail cases:
          - empty string or contains spaces
          - extension is different from the current extension
    @success:
          - filename_ updated
          - last_modified_ and last_modified_timestamp_ updated
    */

    timestamp getLastModified() const;

};

#endif