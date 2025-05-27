#include <iostream>
#include <variant>
using namespace std;

enum class ErrorCode
{
    None = 0, NotFound = 1, NoAccess = 2
};

variant <string, ErrorCode> readFile(string& pathFile)
{

    return {};
} 

// we can also you optional here.

// variant is the type of the class which give us the ability to store multiple data types

int main()
{
    variant<string, int, double> data;
    data = "haseeb";

    cout << "Data: " << get<string>(data) << endl;
    // data.index(); // 0 => string, 1=> int, 2=>Double

    auto value2 = get_if<string>(&data);

    cout << "value address: " << value2 << endl;
    cout << "value : " << *value2 << endl;

    data = 23;
    cout << "Data: " << get<int>(data) << endl;
    // cout << "Data: " <<  get<double>(data) << endl;

    data = 34.23;
    cout << "Data: " << get<double>(data) << endl;
    // cout << "Data: " <<  get<int>(data) << endl;

    auto value = get_if<string>(&data);

    cout << "value address: " << value << endl;

    return 0;
}