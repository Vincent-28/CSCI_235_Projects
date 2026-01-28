    // default constructor (should set default name + permissions + timestamps)
    File f0;
    std::cout << "f0 name: " << f0.getFilename() << "\n";

    // parameterized constructor: (no dot) → should append .txt
    File f1("notes", true, true);
    std::cout << "f1 name: " << f1.getFilename() << "\n";

    // param ctor: trailing dot → should append "txt" (no extra dot)
    File f2("report.", true, true);
    std::cout << "f2 name: " << f2.getFilename() << "\n";

    // param ctor: dotfile allowed as-is
    File f3(".env", true, true);
    std::cout << "f3 name: " << f3.getFilename() << "\n";

    // setFilename: same extension → should succeed
    bool ok1 = f1.setFilename("notes.txt");
    std::cout << "setFilename(notes.txt) on f1 ok? " << ok1 << "\n";

    // setFilename: different extension → should fail
    bool ok2 = f1.setFilename("notes.pdf");
    std::cout << "setFilename(notes.pdf) on f1 ok? " << ok2 << "\n";

    // setReadable / setWritable should always update last-modified timestamp
    auto before = f1.getLastModified();
    f1.setReadable(true);
    auto afterR = f1.getLastModified();
    f1.setWritable(false);
    auto afterW = f1.getLastModified();

    std::cout << "before: "  << FileUtils::timestampToString(before)  << "\n";
    std::cout << "afterR: "  << FileUtils::timestampToString(afterR)  << "\n";
    std::cout << "afterW: "  << FileUtils::timestampToString(afterW)  << "\n";