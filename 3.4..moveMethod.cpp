#include <iostream>
#include <cstring>

using namespace std;

class String
{
private:
    char *data;
    int size;

public:
    String() = default;
    String(String &&other)
    {
        cout << "Move: \n";
        size = other.size;
        data = other.data;

        other.size = 0;
        other.data = nullptr;
    }
    String(const char *tdata)
    {
        cout << "Created." << endl;
        size = strlen(tdata);
        data = new char[size + 1];
        memcpy(data, tdata, size + 1);
    }
    String(const String &other)
    {
        cout << "Copy Constructor." << endl;
        size = other.size;
        data = new char[size + 1];
        memcpy(data, other.data, size + 1);
    }
    void printName()
    {
        for (auto i = 0; i < size; i++)
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
    Entity( String&& tname) : name(move(tname)) {};

    void printName()
    {
        name.printName();
    }
};

int main()
{
    String string1 = "ehllo";
    // String dsest = string1 ; // copy constructor

    // both are same
    // String destination = (String&&)string1; 
    // String destination((String&&)string1); 
    
    String destination(move(string1)); 

    destination.printName();

    return 0;
}