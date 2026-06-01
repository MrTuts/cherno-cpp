#include <iostream>
#include <array>
#include "Log.h"

void ReferencingArray()
{
  int example[5];     // array of 5 integers uninitialized
  int *ptr = example; // example is just a pointer to the first element of the array
  example[0] = 1;
  example[1] = 2;
  /* these all do the same thing */
  example[2] = 3;
  *(ptr + 2) = 6; // sets example[2] to 6, same as example[2] = 6; The two will add number of bytes based on the type of the pointer
  // Here we are adding char*, which makes the pointer arithmetic add 1 byte, so we are adding 8 bytes;
  // we want to set it to 6, so we must cast it back to int* before dereferencing it
  *(int *)((char *)ptr + 8) = 8;

  example[3] = 4;
  example[4] = 5;

  for (int i = 0; i < 5; i++)
  {
    example[i] = i + 1; // sets example[0] to 1, example[1] to 2, etc.
  }

  Log(example[0]);                   // prints 1
  Log(example[5]);                   // this would be out of bounds, but C++ allows it, it does not check for this
  std::cout << example << std::endl; // prints the memory address of the first element of the array
}

namespace
{
  class EntityStack
  {
  public:
    // we need static, because the size of the array must be known at compile time
    static const int ARR_SIZE = 5;
    int arr[ARR_SIZE];

    EntityStack()
    {
      for (int i = 0; i < ARR_SIZE; i++)
      {
        arr[i] = i + 1; // sets arr[0] to 1, arr[1] to 2, etc.
      }
    }
  };

  class EntityHeap
  {
  public:
    int *arr = new int[5];

    EntityHeap()
    {
      for (int i = 0; i < 5; i++)
      {
        arr[i] = i + 1; // sets arr[0] to 1, arr[1] to 2, etc.
      }
    }
  };
}

void CreatingArray()
{
  // init on stack
  int example[5];
  // init on heap, must be deleted manually with delete[] example2; to avoid memory leak
  // If we have a function returning new array (create in that function), we would have to create it on heap, because if we create it on stack,
  // it would be destroyed when the function returns, and we would have a dangling pointer
  int *example2 = new int[5];

  // this would create and initialize the array arr on the stack as part of the Entity object
  EntityStack e;
  // this would create and initialize the array arr on the heap as part of the Entity2 object;
  // the pointer to the array is stored on the stack as part of the Entity2 object, but the array itself is on the heap
  EntityHeap e2;

  /* There is no simple method to get the size of the array */
  // The best way is to hold the size of the array in a separate variable.
  // Here are some workarounds to get the size of the array, but they are not reliable and should not be used in production code:
  // this would give us the size of the array in bytes, which is 5 * sizeof(int) = 20 bytes
  sizeof(example);
  // this would give us the number of elements in the array, which is 5
  int count = sizeof(example) / sizeof(int);
  // this would be size of pointer (8 bytes on 64-bit system) divided by size of int (4 bytes), which would give us 2,
  // which is not correct, because example2 is a pointer to the first element of the array, not the array itself
  int count2 = sizeof(example2) / sizeof(int);

  // OR we use C++11 standard array
  // this also has bounds checking. There is a bit overhead compared to regular arrays, but it is safer to use
  // <type, size> template parameters, where type is the type of the elements and size is the number of elements in the array
  std::array<int, 5> example3;
  example3.fill(0); // initialize all elements to 0
  int count3 = example3.size();

  delete[] example2; // free the memory allocated on the heap
}

void Arrays()
{
  LogSectionTitle("Arrays");
  ReferencingArray();
  CreatingArray();
}