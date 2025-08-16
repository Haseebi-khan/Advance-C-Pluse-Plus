#include <iostream>
using namespace std;

class base1
{
public:
    base1()
    {
        cout << "base1" <<endl;
    }
    void p()
    {
        cout << "111111 " << endl;
    }
};

class base2
{
public:
    base2()
    {
        cout << "base2" <<endl;
    }
    void p()
    {
        cout << "222222 " << endl;
    }
};
class base3 : public base1, public base2
{
    int x;

public:
    // void p()
    // {
    //    base2::p();
    //    base1::p();
    // }

public:
};


int main()
{   
    int arr[3] = {34,56,23};

    int (*wholearr)[3] = &arr;
    cout << wholearr << endl; 
    cout << *(wholearr) << endl; 
    cout << *(*wholearr+2) << endl;   // correct Way. 
    cout << **(wholearr)+1 << endl; 

    // (*wholeBlockOfArray)[i]

    cout << (*wholearr)[0] <<endl;
    cout << (*wholearr)[1] <<endl;
    cout << (*wholearr)[2] <<endl;

    base3 d;
    cout << "\n\n\n\n";
    
    // d.p() //  error: request for member 'p' is ambiguous
    
    
    d.base1::p();
    d.base2::p();


    return 0;
}


