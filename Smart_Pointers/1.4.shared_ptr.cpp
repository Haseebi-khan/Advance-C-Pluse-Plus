#include <iostream>
#include <memory>
using namespace std;

// shared_ptr
// By using shared_ptr, more than one pointer can point to same object at a time, 
// and it will maintain a reference counter using the use_count() method.

int main()
{
    int num = 10;
    
    shared_ptr <int> ptr1(new int(num));
    
    cout << "Pointer point at ptr1 " << *ptr1 << ". Adress: " <<  ptr1 << endl;

    shared_ptr <int> ptr2;
    shared_ptr <int> ptr3;

    ptr2 = ptr1;
    ptr3 = ptr2;


    cout << "Pointer point at ptr2 " << *ptr2 << ". Adress: " <<  ptr1 << endl;
    cout << "Pointer point at ptr3 " << *ptr3 << ". Adress: " <<  ptr1 << endl;
    cout << "\n";


    cout << "Use_Count Method: " << ptr3.use_count() << "\n\n" << endl; 

    return 0;
}




// struct B; // Forward declaration

// struct A {
//     shared_ptr<B> bptr;
// };

// struct B {
//     shared_ptr<A> aptr;
// };

// int main() {
//     auto a = make_shared<A>();
//     auto b = make_shared<B>();

//     a->bptr = b;
//     b->aptr = a;

//     // Memory leak: both shared_ptrs keep each other alive
// }
