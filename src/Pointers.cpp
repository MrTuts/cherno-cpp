#include <iostream>
#include "Log.h"

void HeapMemoryAllocationExample()
{
  Log("   HEAP MEMORY (DYNAMIC MEMORY ALLOCATION)");
  // allocate memory on the heap (dynamic memory allocation) of size 8 bytes (enough for an int or a double) and get a pointer to it
  char *buffer = new char[8];
  Log("Buffer allocated on the heap:");
  Log(buffer);

  // memset(at pointer buffer, fill 65, for 8 bytes [the size of the buffer])
  // set all bytes in the buffer to 65. Meaning all 8 bytes are set to 65
  // if we would pass size of buffer e.g. 10, it would place value 65 in the first 8 bytes,
  // and then it would write 65 to the next 2 bytes, which are not allocated for the buffer, which can lead to undefined behavior (overwriting other data in memory, crashing the program, etc.).
  std::memset(buffer, 65, 8);
  Log("Buffer filled with 65 (ASCII 'A'):");
  Log(buffer);

  // since this is heap allocated, we need to free the memory when we're done with it, otherwise we will have a memory leak (memory that is allocated but not freed, which can lead to running out of memory).
  // use [] because we allocated an array of chars, if we allocated a single char, we would use delete without [].
  delete[] buffer; // free the allocated memory
  Log("Buffer deleted from the heap:");
  Log(buffer);
}

void PointerToPointerExample()
{
  Log("   You let's put a pointer to a pointer!");
  char *buffer = new char[8];
  std::memset(buffer, 65, 8);
  Log("Buffer allocated on the heap:");
  Log(buffer);

  // a pointer is also stored in memory, so we can have a pointer to a pointer (pointer to a memory address that holds another memory address).
  char **ptrToPtr = &buffer; // pointer to a pointer, initialized with the address of the buffer pointer
  delete[] buffer;           // free the allocated memory
}

void Pointers()
{
  LogSectionTitle("Pointers");

  // typeless pointer of memory address at 0 - null pointer
  void *ptr = 0; // or NULL or nullptr (C++11);

  int var = 8;
  // & is the address-of operator, it gives us the memory address of var
  void *ptrIntAsVoid = &var; // pointer to an int, initialized with the address
  // this is quite the same as above, but with a specific type of pointer (pointer to int).
  // Types don't matter for the compiler, but they matter for us, so we can manipulate the data at the address in a correct way.
  int *ptrIntAsInt = &var;                 // pointer to an int, initialized with the address
  double *ptrIntAsDouble = (double *)&var; // pointer to a double, initialized with the address

  // rewrite data at the address of var through the pointer
  *ptrIntAsInt = 10; // dereference the pointer and assign a new value to the variable at the address
  // *ptrIntAsVoid = 10; // This won't compile, because the compiler doesn't know what type of data is at the address, so it doesn't know how to manipulate it.
  Log("Set var to 10 through the int pointer");
  Log(var);
  *ptrIntAsDouble = 10.0; // dereference the pointer and assign a new value to the variable at the address
  Log("Set var to 10 through the double pointer");
  Log(var);

  HeapMemoryAllocationExample();

  PointerToPointerExample();
}