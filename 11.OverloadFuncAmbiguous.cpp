#include <iostream>
using namespace std;

class A {
public:
    void fun(int x) { cout << "A::fun(int)\n"; }
};

class B {
public:
    void fun(double y) { cout << "B::fun(double)\n"; }
};

class C : public A, public B {
public:
    using A::fun; // Brings A's fun into scope
    using B::fun;
};

int main() {
    C obj;
    obj.fun(10);    // A::fun(int)
    obj.fun(3.14);  // B::fun(double)
}
