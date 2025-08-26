#include <iostream>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

int main()
{
    fs::path p = ("./file2.txt");
    fs::file_status status = fs::status(p);
    
    cout << "Type: " << (int)status.type() << endl;
    cout << "Permission: " << (int)status.permissions() << endl; 
    
    switch (status.type()) 
    {
        case fs::file_type::regular:
            cout << "Type: Regular file\n"; 
            break;
        case fs::file_type::directory:
            cout << "Type: Directory\n"; 
            break;
        case fs::file_type::symlink:
            cout << "Type: Symlink\n"; 
            break;
        case fs::file_type::not_found:
            cout << "Type: Not found\n"; 
            break;
        default:
            cout << "Type: Other/Unknown\n"; 
            break;
    }

    auto perms = status.permissions();
    cout << "Permissions: ";
    cout << ((perms & fs::perms::owner_read) != fs::perms::none ? "r" : "-");
    cout << ((perms & fs::perms::owner_write) != fs::perms::none ? "w" : "-");
    cout << ((perms & fs::perms::owner_exec) != fs::perms::none ? "x" : "-");
    cout << endl;

    
    
    
    return 0;
}