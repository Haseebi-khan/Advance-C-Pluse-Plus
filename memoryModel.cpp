// Memory Model in C++
// The memory model in C++ defines how the program stores and accesses data in computer memory. 

// Stack Memory
// Stack memory is used for automatic storage duration variables, such as local variables and function call data.
// Stack memory is managed by the compiler, and it's allocation and deallocation are done automatically. 

// void functionExample() {
//     int x = 10; // x is stored in the stack memory
// }

// =======================================================================================================================

// Heap Memory
// Heap memory is used for dynamic storage duration variables, such as objects created using the new keyword. 
// The programmer has control over the allocation and deallocation of heap memory using new and delete operators. 

// void functionExample() {
//     int* p = new int; // dynamically allocated int in heap memory
//     *p = 10;
//     // more code
//     delete p; // deallocate memory
// }

// =======================================================================================================================

// Data Segment
// The Data segment is composed of two parts: the initialized data segment and the uninitialized data segment. 
// The initialized data segment stores global, static, and constant variables with initial values, 
// whereas the uninitialized segment stores uninitialized global and static variables.

// // Initialized data segment
// int globalVar = 10; // global variables
// static int staticVar = 10; // static local variables
// const int constVar = 10; // constant variables with value

// // Uninitialized data segment
// int globalVar; // uninitialized global variables
// Code Segment
// The Code segment (also known as the Text segment) stores the executable code (machine code) of the program. It's usually located in a read-only area of memory to prevent accidental modification.

// void functionExample() {
//     // The machine code for this function is stored in the code segment.
// }

// =======================================================================================================================
