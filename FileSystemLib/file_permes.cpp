#include <iostream>
#include <filesystem>
using namespace std;

namespace fs = filesystem;

void demo_perms(std::filesystem::perms p)
{
    using std::filesystem::perms;
    // lambda func 
             // [](){} lambda
    auto show = [=](char op, perms perm) 
    {
        std::cout << (perms::none == (perm & p) ? '-' : op);
    };
    show('r', perms::owner_read);
    show('w', perms::owner_write);
    show('x', perms::owner_exec);
    show('r', perms::group_read);
    show('w', perms::group_write);
    show('x', perms::group_exec);
    show('r', perms::others_read);
    show('w', perms::others_write);
    show('x', perms::others_exec);
    std::cout << '\n';
}


int main()
{   
    fs::path p = ("file2.txt");

    fs::file_status s =  fs::status(p);

    demo_perms(s.permissions());


    return 0;
}