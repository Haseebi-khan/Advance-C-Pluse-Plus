#include <iostream>
#include <filesystem>
using namespace std;

namespace fs = filesystem;

int main()
{
    const fs::path from("/Advance-C-Pluse-Plus/FileSystemLib/file1.png"), to("/Advance-C-Pluse-Plus/FileSystemLib/copy/");

    try
    {
        fs::copy_file(from,to);
    }
    catch(fs::filesystem_error const& ex)
    {
        std::cerr <<"what: " <<ex.what() << '\n';
        std::cerr <<"path1: " <<ex.path1() << '\n';
        std::cerr << "path2: " << ex.path2() << '\n';
        std::cerr << "code: "<< ex.code() << '\n';
        std::cerr << "codevalue: "<<ex.code().value() << '\n';
        std::cerr << "Code message: " << ex.code().message() << '\n';
        std::cerr << "Code : " << ex.code().category().name() << '\n';
    }
    
    

    // All functions have non-throwing equivalents
    std::error_code ec;
    std::filesystem::copy_file(from, to, ec); // does not throw
    std::cout << "\nNon-throwing form sets error_code: " << ec.message() << '\n';
    
    
    return 0;
}


                    // OUTPUT

// PS D:\Codes\Advance-C-Pluse-Plus\FileSystemLib> ./run.exe
// what: filesystem error: cannot copy file: No such file or directory [/Advance-C-Pluse-Plus/FileSystemLib/file1.png] [/Advance-C-Pluse-Plus/FileSystemLib/copy/]
// path1: "/Advance-C-Pluse-Plus/FileSystemLib/file1.png"
// path2: "/Advance-C-Pluse-Plus/FileSystemLib/copy/"
// code: generic:2
// codevalue: 2
// Code message: No such file or directory
// Code : generic

// Non-throwing form sets error_code: No such file or directory
