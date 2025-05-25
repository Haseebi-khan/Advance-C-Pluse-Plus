#include <iostream>
#include <memory>
using namespace std;

// ==============================   unique_ptr   ==============================
// unique_ptr stores one pointer only at a time. 
// We cannot copy unique_ptr, only transfer ownership of the object to another unique_ptr using the move() method.
// ============================================================================

int main()
{
    int num = 30;
    unique_ptr <int> ptr1( new int(num));  
    cout << "Pointer point on ptr1 : " << *ptr1<<endl; 
    unique_ptr <int> ptr2;  
    ptr2 = move(ptr1);
    cout << "Pointer point on ptr2 : " << *ptr2<<endl; 
    
    cout << "Checking ptr1 : " << ptr1 <<endl; 

    // cout << "Trying to COPY PTR2 To PTR1\n";

    // ptr2 = ptr1;
    
    return 0;
}