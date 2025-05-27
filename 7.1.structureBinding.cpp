#include <iostream>
#include <tuple>
#include <string>

using namespace std;

tuple < string, int > CreatePerson()
{
    return {"Haseeb", 20};
}

// dealing with Multiple return type.
int main()
{
    auto person = CreatePerson();
    string name = get<0>(person);
    int age = get<1>(person);
    cout << "Name: " << name << " Age: " << age << endl;
    tie(name, age ) = CreatePerson();    
    
    // Structure Binding
    // =================================================================================/
    auto [name1, age1] = CreatePerson();
    cout << "Name: " << name1 << " Age: " << age1 << endl;
    // =================================================================================/
    
    return 0;
}