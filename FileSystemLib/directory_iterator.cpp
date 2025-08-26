#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

namespace fs = filesystem;

// int main()
// {
//     fs::path p = "/Advance-C-Pluse-Plus/FileSystemLib";

//     // PS D:\Codes\Advance-C-Pluse-Plus\FileSystemLib> ./run.exe
//     // terminate called after throwing an instance of 'std::runtime_error'
//     // what():  File is not open.
//     // PS D:\Codes\Advance-C-Pluse-Plus\FileSystemLib> 

//     fstream file;
//     file.open( p / "file2", std::ios::in);

//     if (!file.is_open())
//     {
//         throw::runtime_error("File is not open.");
//     }
//     else
//     {
//         string line;
//         while (getline(file, line)) 
//         {
//             cout << line << endl;
//         }       
//     }

//     return 0;
// }
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm> // for std::for_each

using namespace std;
namespace fs = std::filesystem;

int main()
{
    const fs::path p = "D:\\Codes\\Advance-C-Pluse-Plus\\FileSystemLib\\copy";

    // Create directory and files
    fs::create_directories(p / "copy2");
    ofstream(p / "file2.txt");
    ofstream(p / "file3.txt");

    // Simple directory iteration
    cout << "directory_iterator:\n";
    for (auto const& dir_entry : fs::directory_iterator{p}) {
        cout << dir_entry.path() << endl;
    }

    // Directory iterator as a range using std::for_each
    cout << "\ndirectory_iterator as a range:\n";
    std::for_each(fs::directory_iterator{p},
                  fs::directory_iterator{},
                  [](const auto& dir_entry) {
                      cout << dir_entry.path() << '\n';
                  });

    // Recursive iteration
    cout << "\nrecursive_directory_iterator:\n";
    for (auto const& dir_entry : fs::recursive_directory_iterator{p}) {
        cout << dir_entry.path() << '\n';
    }

    return 0;
}



