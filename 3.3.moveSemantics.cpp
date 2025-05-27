
// What are Move Constructors?
// In C++, move constructors is a type of constructor that works on the r-value references and
// move semantics (move semantics involves pointing to the already existing object in the memory).

// Unlike copy constructors that work with the l-value references and
// copy semantics(copy semantics means copying the actual data of the object to another object),
// move constructor transfer the ownership of the already existing object to the new object without making any copy of it.
// It makes the new object point to the already existing object in the heap memory.

#include <iostream>
#include <cstring>
using namespace std;

class String
{
private:
    char *data;
    int _size;

public:
    String() = default;
    ~String()
    {
        cout << "Destoried." << endl;
        delete[] data;
    }
    String(const char *tdata)
    {
        cout << "Created." << endl;
        _size = strlen(tdata);
        data = new char[_size + 1];
        memcpy(data, tdata, _size+1);
    }

    // Move Constructor
    String(String&& other) noexcept
    {
        cout << "Move." << endl;
        _size = other._size;
        data = other.data;

        // Neccessary thing to do in Move sanematic.
        other.data = nullptr;
        other._size = 0;
    }

    String(const String &other)
    {
        cout << "Copy Constructor." << endl;
        _size = other._size;
        data = new char[_size + 1];
        memcpy(data, other.data, _size+1);
    }

    void printName()
    {
        for (auto i = 0; i < _size; i++)
        {
            cout << data[i];
        }
        cout << "\n";
    }
};

class Entity
{
private:
    String name;

public:
    Entity(const String& tname ) : name(tname) {};
    // Move Constructor
    Entity( String&& tname) : name((String&&)tname) {};

    void printName()
    {
        name.printName();
    }
};

int main()
{

    Entity entity(("Haseeb"));
    entity.printName();

    // cout <<"\n\n\nObject type.\n";
    // Entity entity2(String("Haseeb"));
    // entity2.printName();

    return 0;
}

// class Simple
// {
// private:
//     int *data;

// public:
//     // Constructor
//     Simple(int value) : data(new int(value))
//     {
//         cout << "Constructor called, data = " << *data << endl;
//     }

//     // Destructor
//     ~Simple()
//     {
//         delete data;
//         cout << "Destructor called" << endl;
//     }

//     // Move constructor
//     Simple(Simple &&other) : data(other.data)
//     {
//         // nullify the other object resource
//         other.data = nullptr;
//         cout << "Move constructor called" << endl;
//     }

//     // Move assignment operator
//     Simple &operator=(Simple &&other)
//     {
//         if (this != &other)
//         {
//             delete data;          // Free existing resource
//             data = other.data;    // Transfer ownership
//             other.data = nullptr; // Nullify source
//             cout << "Move assignment called" << endl;
//         }
//         return *this;
//     }

//     // Disable copy constructor and copy assignment operator
//     Simple(const Simple &) = delete;
//     Simple &operator=(const Simple &) = delete;

//     // Function to print the value
//     void print()
//     {
//         if (data)
//         {
//             cout << "Data: " << *data << endl;
//         }
//         else
//         {
//             cout << "Data is null" << endl;
//         }
//     }
// };

// int main()
// {
//     // Create a Simple object with value 42
//     Simple obj1(42);
//     obj1.print();

//     // Move obj1 to obj2 using move constructor
//     Simple obj2 = move(obj1);
//     // Print obj2's data
//     obj2.print();
//     // Print obj1's data after move
//     obj1.print();

//     // Create another Simple object with value 84
//     Simple obj3(84);
//     // Move obj2 to obj3 using move assignment
//     obj3 = move(obj2);
//     obj3.print();
//     obj2.print();

//     return 0;
// }

// // C++ program for demonstrating the use of
// // move constructor
// #include <iostream>
// #include <vector>
// using namespace std;

// // Move Class
// class Move
// {
// private:
//     // Declare the raw pointer as
//     // the data member of class
//     int *data;

// public:
//     // Constructor
//     Move(int d)
//     {
//         // Declare object in the heap
//         data = new int;
//         *data = d;
//         cout << "Constructor is called for " << d << endl;
//     };

//     // Copy Constructor
//     Move(const Move &source)
//         : Move{*source.data}
//     {

//         // Copying the data by making
//         // deep copy
//         cout << "Copy Constructor is called -"
//              << "Deep copy for " << *source.data << endl;
//     }

//     // Move Constructor
//     Move(Move &&source)
//         : data{source.data}
//     {

//         cout << "Move Constructor for " << *source.data
//              << endl;
//         source.data = nullptr;
//     }

//     // Destructor
//     ~Move()
//     {
//         if (data != nullptr)

//             // If pointer is not pointing
//             // to nullptr
//             cout << "Destructor is called for " << *data
//                  << endl;
//         else

//             // If pointer is pointing
//             // to nullptr
//             cout << "Destructor is called"
//                  << " for nullptr " << endl;

//         // Free up the memory assigned to
//         // The data member of the object
//         delete data;
//     }
// };

// // Driver Code
// int main()
// {
//     // Vector of Move Class
//     vector<Move> vec;

//     // Inserting Object of Move Class
//     vec.push_back(Move{10});
//     vec.push_back(Move{20});
//     return 0;
// }