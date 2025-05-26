// #include <iostream>

// using namespace std;

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

#include <iostream>

using namespace std;

struct RefHolder
{
    const int &&m_x;
    RefHolder(int &&x) : m_x((int &&)x) {}
    RefHolder(const RefHolder &&other) : m_x((int &&)other.m_x) {}
};

int addOne(const int &&ref)
{
    return ref + 1;
}

int main()
{
    int x = 2;
    const RefHolder refHolder((int &&)x);
    const RefHolder otherRefHolder((RefHolder &&)refHolder);
    int newx = addOne((int &&)refHolder.m_x);
    // refHolder.m_x = addOne((int &&)refHolder.m_x);
    // refHolder.m_x = addOne(refHolder.m_x);BF


    cout << "newx: " << newx << endl;
    cout << "Refholder: " << refHolder.m_x << endl;
    cout << "Ohter Refholder: " << otherRefHolder.m_x << endl;

    return 0; 
}


