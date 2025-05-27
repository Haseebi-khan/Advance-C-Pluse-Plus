#include <iostream>

using namespace std;

// lvalue reference:
// An lvalue is an expression that will appear on the left-hand side or on the right-hand side of an assignment. such as i = 10;
// Simply, a variable or object that has a name and memory address.
// It uses one ampersand (&).

int &getValue()
{
    static int value = 10;
    return value;
}

void setValue(int &value)
{
    cout << "L Values\n";
}

void setValue(const int &value)
{
    cout << "R Values\n";
}

void show(string &name)
{
    cout << name << endl;
    cout << "L Values\n";
}

void show(const string &name)
{
    cout << name << endl;
    cout << "R Values\n";
}

int main()
{
    int i = 10;

    cout << "Value : " << getValue() << endl;
    getValue() = 40;
    cout << "Value : " << getValue() << endl;

    setValue(i); // setValue func

    setValue(10); // const setValue func

    string fname = "Haseeb ";
    string lname = "Khan";

    string name = fname + lname;

    show(fname + lname); // const show func
    show(name);          // show func

    return 0;
}

// int main()
// {
//     // I value and R value referenec.
//     int num = 10;
//     cout << "Ivalue Reference: " << &num << endl;

//     int& Ivalue_ref = (int&)num;
//     int&& rvalue_ref = (int&&)num;

//     cout << "Ivalue_ref: " << Ivalue_ref <<endl;

//     Ivalue_ref = 20;
//     cout << "num Reference: " << num << endl;
//     cout << "num Reference: " << &num << endl;

//     cout << "Ivalue_ref: " << Ivalue_ref << endl;
//     cout << "Ivalue_ref: " << &Ivalue_ref << endl;

//     rvalue_ref = 0;

//     cout << "num Reference: " << num << endl;
//     cout << "num Reference: " << &num << endl;

//     cout << "Rvalue_ref: " << rvalue_ref << endl;
//     cout << "Rvalue_ref: " << &rvalue_ref << endl;

// // Ivalue Reference: 0x19589ffa9c
// // Ivalue_ref: 10
// // num Reference: 20
// // num Reference: 0x19589ffa9c
// // Ivalue_ref: 20
// // Ivalue_ref: 0x19589ffa9c
// // num Reference: 0
// // num Reference: 0x19589ffa9c
// // Rvalue_ref: 0
// // Rvalue_ref: 0x19589ffa9c

// //  those references are incompatible, even if they behave the same
// //  you can't pass a reference to a function expecting a reference of the other color (e.g. you can't pass an int& in a function expecting an int&&).
// //  However, because they behave identically, we can cast from one to the other:

//     return 0;
// }

// #include <iostream>

// using namespace std;

// struct RefHolder
// {
//     const int &&m_x;
//     RefHolder(int &&x) : m_x((int &&)x) {}
//     RefHolder(const RefHolder &&other) : m_x((int &&)other.m_x) {}
// };

// int addOne(const int &&ref)
// {
//     return ref + 1;
// }

// int main()
// {
//     int x = 2;
//     const RefHolder refHolder((int &&)x);
//     const RefHolder otherRefHolder((RefHolder &&)refHolder);
//     int newx = addOne((int &&)refHolder.m_x);
//     // refHolder.m_x = addOne((int &&)refHolder.m_x);
//     // refHolder.m_x = addOne(refHolder.m_x);BF

//     cout << "newx: " << newx << endl;
//     cout << "Refholder: " << refHolder.m_x << endl;
//     cout << "Ohter Refholder: " << otherRefHolder.m_x << endl;

//     return 0;
// }
