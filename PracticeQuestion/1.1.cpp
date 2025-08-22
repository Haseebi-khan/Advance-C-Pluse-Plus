#include <iostream>
using namespace std;

int main()
{
    // =============================================================================================================
    // =============================================================================================================

    // What [] means in lambda:
    
    // They specify which variables from the surrounding scope the lambda can "capture" and use inside its body.

    // Common forms:
    
    // [] → capture nothing.
    
    // [=] → capture all variables from surrounding scope by value.

    // [&] → capture all variables from surrounding scope by reference.
    
    // [x] → capture only variable x by value.
    
    // [&x] → capture only variable x by reference.
    
    // [=, &y] → capture everything by value, but capture y by reference.
    
    // [& , x] → capture everything by reference, but capture x by value.
    
    int a = 10, b = 20;

    auto fun = [&](int a, int b)
    {
        cout << "a + b = " << (a + b) << endl;
        double x = (a + b);
        a = 0, b = 0;
        return x;
    };

    // =============================================================================================================
    // =============================================================================================================
    double value = fun(a, b);

    cout << "A = " << a << " , B = " << b << endl;

    cout << value << endl;

    cout << endl;

    for (int i{}; i < 3; i++)
    {
        cout << i << " ";
    }
    cout << endl;
    for (int i{}; i < 3; ++i)
    {
        cout << i << " ";
    }

    

    return 0;
}