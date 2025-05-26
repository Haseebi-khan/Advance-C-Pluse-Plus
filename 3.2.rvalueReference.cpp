// #include <iostream>

// using namespace std;

// double show(double x)
// {
//     return x;
// }

// double modify(double x)
// {
//     return x;
// }

// int main()
// {
//     //  Term	Think of it as...	Meaning in C++
//     //  lvalue	A label to a memory location	You can take its address using &. It's a "named" object.
//     //  rvalue	A temporary value	A value that doesn't have a name and only exists for a short time.

//     //  lvalue (named object)

//     int x = 5;   // 'x' is an lvalue
//     int *p = &x; // you can take address: OK

//     //  rvalue (temporary value)

//     int y = 5 + 3; // '5 + 3' is an rvalue
//     // int* q = &(5 + 3); // ❌ ERROR! You can't take address of an rvalue

//     // lvalue reference

//     void show(const int &val); // Accepts lvalues and rvalues

//     // int x = 10;
//     show(x);     // OK (lvalue)
//     show(5 + 2); // OK (rvalue too)
//     // rvalue reference

//     // void modify(int&& val);     // Accepts only rvalues

//     // modify(5 + 3);   // ✅ OK (temporary value)
//     // modify(x);       // ❌ ERROR (x is an lvalue)

//     // If you want to pass x as an rvalue:

//     modify(std::move(x)); // ✅ OK

//     return 0;
// }

#include <iostream>

using namespace std;

class Container
{
private:
    int* m_data;
public:
    Container() : m_data(new int(42)) {
        std::cout << "Default constructor\n";
    }

    // Copy constructor
    Container(const Container& other) : m_data(new int(*other.m_data)) {
        std::cout << "Copy constructor\n";
    }

    // Move constructor
    Container(Container&& other) noexcept : m_data(other.m_data) {
        other.m_data = nullptr;
        std::cout << "Move constructor\n";
    }

    ~Container() {
        delete m_data;
        std::cout << "Destructor\n";
    }
    void value(){
        cout << "M_Data: " << *m_data << endl;
    }
};

// Factory function (must return by value to trigger move)
Container makeContainer() {
    return Container(); // temporary object — an rvalue
}

int main()
{

    const Container c1 = makeContainer(); // Move constructor is called, then c1 becomes const
    Container copy{c1};                   // c1 is const => Copy constructor is used
    Container c2 = makeContainer();       // Move constructor is called
    Container steal{std::move(c2)};       // std::move makes c2 into an rvalue => Move constructor
    steal.value();

    return 0;
}