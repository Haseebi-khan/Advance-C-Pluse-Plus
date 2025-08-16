#include <iostream>
#include <memory>

using namespace std;

// Key Functions of weak_ptr
// Function 	Description
// .lock()  	Returns a shared_ptr if the object is still alive, or nullptr if expired.
// .expired() 	Checks whether the managed object has already been deleted.
// .reset() 	Releases the weak reference.
// .use_count()	Returns how many shared_ptrs are managing the object.

int main()
{
    int num = 10;
    
    shared_ptr <int> ptr1(new int(num));
    
    weak_ptr <int> ptr2(ptr1);

    cout << "ptr1: " << *ptr1 <<endl;

    if (auto temp = ptr2.lock())
    {
        cout << "temp: " << *temp <<endl;
    }

    ptr1 = nullptr;

    if (auto temp = ptr2.lock())
    {
        cout << "temp: " << *temp <<endl;
    }
    else
    {
        cout << "ptr is expired";
    }

    shared_ptr<int> sp = make_shared<int>(99);
    weak_ptr<int> wp = sp;

    if (auto temp = wp.lock()) {
        cout << "Value: " << *temp << endl;
    }

    wp.reset();  // manually clear the weak pointer

    cout << "After reset, expired? " << wp.expired() << endl;  // true
    
// =============================================================================================================
// =================================   best representation of weak pointers. ===================================
// =============================================================================================================
    {
        shared_ptr<int> sp = make_shared<int>(42);
        wp = sp;

        cout << "\n\nInside block:" << endl;
        cout << "Is expired? " << wp.expired() << endl;  // false
    }

    cout << "\n\nOutside block:" << endl;
    cout << "Is expired? " << wp.expired() << endl;  // true (sp is destroyed)

// =============================================================================================================
// =============================================================================================================

    return 0;
}











// struct B; // Forward declaration

// struct A {
//     shared_ptr<B> bptr;
// };

// struct B {
//     weak_ptr<A> aptr;  // <-- Now no circular reference
// };

// int main() {
//     auto a = make_shared<A>();
//     auto b = make_shared<B>();

//     a->bptr = b;
//     b->aptr = a;

//     // Memory will be freed properly
// }





