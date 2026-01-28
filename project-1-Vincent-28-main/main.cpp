#include <iostream>
#include "File.hpp"
#include "FileUtils.hpp"

int main() {
    File f0;
    std::cout << "f0 name: " << f0.getFilename() << "\n";

    File f1("notes", true, true);
    std::cout << "f1 name: " << f1.getFilename() << "\n";

    File f2("report.", true, true);
    std::cout << "f2 name: " << f2.getFilename() << "\n";

    File f3(".env", true, true);
    std::cout << "f3 name: " << f3.getFilename() << "\n";

    bool ok1 = f1.setFilename("notes.txt");
    std::cout << "setFilename(notes.txt) on f1 ok? " << ok1 << "\n";

    bool ok2 = f1.setFilename("notes.pdf");
    std::cout << "setFilename(notes.pdf) on f1 ok? " << ok2 << "\n";

    auto before = f1.getLastModified();
    f1.setReadable(true);
    auto afterR = f1.getLastModified();
    f1.setWritable(false);
    auto afterW = f1.getLastModified();

    std::cout << "before: "  << FileUtils::timestampToString(before)  << "\n";
    std::cout << "afterR: "  << FileUtils::timestampToString(afterR)  << "\n";
    std::cout << "afterW: "  << FileUtils::timestampToString(afterW)  << "\n";

    std::cout << FileUtils::findFileExtension("..") << std::endl;
    std::cout << FileUtils::findFileExtension("hellohhipdf.") << std::endl;
    std::cout << FileUtils::findFileExtension("aaaaaa") << std::endl;

    return 0;
}
