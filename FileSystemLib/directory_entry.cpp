#include <iostream>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

int main() 
{
    // ( ../ ) will go back to the Dirctory.
    // ( . ) will consider the current Dirctory.
    for ( const fs::directory_entry& entry :  fs::directory_iterator("../"))
    {
        cout<< entry.path();
        if (entry.is_directory())
        {
            cout << "[DIR]"<<endl;
        }
        else if(entry.is_regular_file())
        {
            cout << " : " << entry.file_size() <<endl;
        }
        cout << "\n";         
    }
    
    return 0;
}
