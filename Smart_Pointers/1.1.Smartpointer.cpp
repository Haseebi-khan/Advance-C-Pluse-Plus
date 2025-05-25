// Problems with Normal Pointers
// Memory Leaks: This occurs when memory is repeatedly allocated by a program but never freed. 
// This leads to excessive memory consumption and eventually leads to a system crash. 
// Wild Pointers: A pointer that never be initialize with valid object or address called wild pointer.
// Dangling Pointers: Assume there is a pointer that refers to memory which was deallocated earlier in the program, 
// that pointer is called a dangling pointer.


// Smart Pointers
// Smart pointer is wrapper class over a pointer that acts as a pointer but automatically manages the memory it points to. 
// It ensures that memory is properly deallocated when no longer needed, preventing memory leaks. 
// It is a part of <memory> header file.

// Smart pointers are implemented as templates so we can create a smart pointer to any type of memory.

// Types of Smart Pointers
// auto_ptr
// unique_ptr
// shared_ptr
// weak_ptr