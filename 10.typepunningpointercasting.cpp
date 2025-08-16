#include <iostream>
using namespace std;

class Empty{
public:
    int x;
    Empty(int a){
        x = a;
    }
    void display()
    {
       cout << "Value: " << x; 
    }

};

int main()
{
    Empty a= 9;
    

    int *b = (int*) &a;

    cout << "b: " << *b <<endl;

    *b =10;

    a.display();


    // b = 10;





    

    return 0;
}








