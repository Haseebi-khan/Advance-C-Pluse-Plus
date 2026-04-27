
// Example: Throwing version (no ec)
// fs::path p = "foo.c";
// fs::path abs = fs::absolute(p);  // Throws on error

// Example: Non-throwing version (with ec)
// fs::path p = "foo.c";
// std::error_code ec;
// fs::path abs = fs::absolute(p, ec); // Won’t throw, reports error via ec

// if (ec) {
    //     std::cout << "Error: " << ec.message() << '\n';
    // } else {
        //     std::cout << "Absolute path is " << abs << '\n';
        // }
        
        
        // So in plain English:
        
        // p is the path you want to make absolute.
        
// ec is optional — if you use it, you’re asking the function not to throw exceptions, 
// but instead to set ec with any error info.
#include <iostream>
#include <filesystem>
using namespace std;

#include <system_error> // for std::error_code

namespace fs = std::filesystem;

int main()
{   
    try
    {
        fs::path checkfile = "file1";

        cout << "Current Path is: " << fs::current_path() << endl;
        cout << "Absolute Path for: " << checkfile << " is: " 
             << fs::absolute(checkfile) << endl;

    }
    catch(const fs::filesystem_error& e)
    {
        cerr << "\nFileSystem error: \n" <<  e.what() << '\n';
        cerr << "Path1: " << e.path1() << endl;
        cerr << "Path2: " << e.path2() << endl;

        if (!e.path2().empty())
        {
            cerr << "Path2: " << e.path2() << endl;
        }
    }
    catch(const exception& e)
    {
        cerr << "General exception: " << e.what() << endl;
    }

    cout << "===============================================================\n";
    cout << "=                    ITS SAFE                                 =\n";
    cout << "===============================================================\n\n";


    fs::path p = "";
    std::error_code ec;

    auto absPath = fs::absolute(p, ec); // pass error_code
    if (ec) {
        std::cerr << "Error: " << ec.message() << '\n';
    } else {
        std::cout << "Current path is " << fs::current_path() << '\n';
        std::cout << "Absolute path for " << p << " is " << absPath << '\n';
    }
 
    return 0;
}
