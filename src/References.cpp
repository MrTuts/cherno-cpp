#include "Log.h"

// Passing as value, meaning a COPY of the value is passed to the function, so changes to the parameter inside the function do not affect the original argument.
void Increment(int value)
{
  value++;
}

void IncrementByPointer(int *ptrToValue)
{
  // NOT LIKE THISThis would increment the pointer itself, meaning it would point to the next memory address (which is not what we want).
  // *ptrToValue++;

  // But like this, we dereference the pointer first to get the value at the address, and then we increment that value
  (*ptrToValue)++;
}

void IncrementByReference(int &refToValue)
{
  refToValue++;
}

void References()
{
  LogSectionTitle("References");

  int a = 5;

  // Here the & is part of the type, it specifies that b is a reference to an a.
  // This variable does not exist in memory as a separate variable. It is just an alias for a and only exists in our program, not compiled code.
  int &ref = a;
  // This & specifies the address of a, so b is a pointer to a, meaning b holds the memory address of a.
  // This pointer does exist in memory as a separate variable, it holds the memory address of a.
  int *b = &a; // pointer to a, holds the memory address of a

  ref = 2;
  Log("Value of a after changing ref:");
  Log(a); // a is now 2, because ref is a reference to a,

  Increment(a);
  Log("Value of a after Increment(a):");
  Log(a); // a is still 2, because Increment takes a copy of a,

  IncrementByPointer(&a);
  Log("Value of a after IncrementByPointer(&a):");
  Log(a); // a is now 3, because IncrementByPointer modifies the original value through the pointer

  IncrementByReference(a);
  Log("Value of a after IncrementByReference(a):");
  Log(a); // a is now 4, because IncrementByReference modifies the original value through the reference

  int c = 8;
  ref = c; // This does not change the reference to point to b, it changes the value of a (and ref) to 8, because ref is an alias for a, not a pointer.
  Log("Value of a after ref = c:");
  Log(a); // a is now 8, because ref is an alias for a,

  int *ptr = &a; // pointer to a, holds the memory address of a
  *ptr = 2;      // we are setting the value at the address of a to 2, so a is now 2
  ptr = &c;      // we are setting the pointer to point to the address of c
  *ptr = 2;      // we are setting the value at the address of c to 2, so c is now 2
  Log("Value of a after ptr = &c and *ptr = 2:");
  Log(a); // a is still 2, because we changed the value at the address
  Log("Value of c after ptr = &c and *ptr = 2:");
  Log(c); // c is now 2, because we changed the value at the address
}