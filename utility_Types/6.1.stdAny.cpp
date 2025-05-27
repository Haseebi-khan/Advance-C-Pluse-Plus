#include <iostream>
#include <any>
#include <variant>

using namespace std;

// any and vairant is same.

int main()
{
    any data ;

    data = "sakdjlkasd";
    
    const char* s = any_cast<const char*>(data);
    cout << s << endl;

    any newData = string("Haseeb");
    string  value = any_cast<string>(newData);
    cout << value <<endl;
    

    return 0;
}