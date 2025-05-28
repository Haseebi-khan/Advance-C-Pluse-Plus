#include <iostream>
#include <tuple>
#include <string>

using namespace std;

tuple < string, int > CreatePerson()
{
    return {"Haseeb", 20};
}

struct Person
{
    string name;
    int age;
};


// dealing with Multiple return type.
int main()
{

    Person p[4];
    p[0].name = "Hasnain";
    p[0].age = 20;

    p[1].name = "Ayesha";
    p[1].age = 22;

    p[2].name = "Ali";
    p[2].age = 25;

    p[3].name = "Sara";
    p[3].age = 18;


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

    cout << "\n\n\n\n\n";

    for(auto&[name, age] : p)
    {
        cout << "Name: " << name << " Age: " << age << endl; 
    }

    cout << "\n\n\n\n\n";

    for (auto& psvalue : p)
    {
        string name = psvalue.name;
        int age = psvalue.age;

        cout << "Name: " << name << " Age: " << age << endl; 

    }
    

    
    
    return 0;
}