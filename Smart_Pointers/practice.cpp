#include <iostream>
#include <memory>
using namespace std;



struct B; // Forward declaration

struct A {
    shared_ptr<B> bptr;
};

struct B {
    weak_ptr<A> aptr;  // <-- Now no circular reference
};


int main() {
    auto a = make_shared<A>();
    auto b = make_shared<B>();

    a->bptr = b;
    b->aptr = a;

    cout << a.use_count() <<endl;
    cout << a->bptr.use_count() <<endl;
    cout << b.use_count() <<endl;
    cout << b->aptr.use_count() <<endl;

    b->aptr.reset();
    a->bptr.reset();



    cout << "\n\n\n\n\n" << a.use_count() <<endl;
    cout << a->bptr.use_count() <<endl;
    cout << b.use_count() <<endl;
    cout << b->aptr.use_count() <<endl;


    shared_ptr<int> p (new int(1));
    unique_ptr<int> q (new int (2));
    weak_ptr<int> r = p;

    shared_ptr<string> s (new string("1"));
    unique_ptr<string> t (new string("2"));

    cout << "\n\n\n\n\n";
    cout << "shared ptr: " << sizeof(p) <<endl;
    cout << "unique ptr: " << sizeof(q) <<endl;
    cout << "weak ptr: " << sizeof(r) <<endl;
    cout << "\n\n\n\n\n";
    cout << "shared ptr string: " << sizeof(s) <<endl;
    cout << "Unique ptr string: " << sizeof(t) <<endl;
    string h = "sadsad";
    cout << "string: " << sizeof(h);

    cout << endl;
    return 0;
    // Memory will be freed properly 
}



