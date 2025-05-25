#include <iostream>
#include <memory>
using namespace std;

// Important Note:
// auto_ptr is deprecated since C++11 and removed in C++17. 
// It is not recommended to use it in modern C++ code because it has confusing ownership semantics that often lead to bugs.

int main()
{
   auto_ptr <string> name(new string("Haseeb")); 

   return 0;
}
