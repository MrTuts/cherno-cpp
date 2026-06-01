#include <iostream>
#include <string>
#include "Log.h"

#define YoAllocateMe new
#define YoDeleteMe delete

using String = std::string;

struct Vector3
{
  float x, y, z;

  Vector3() : x(10), y(11), z(12) {} // default constructor to initialize values to 0
};

class Entity
{
private:
  String m_Name;

public:
  Entity() : m_Name("Default") {}
  Entity(const String &name) : m_Name(name) {}
  const String &GetName() const { return m_Name; }
};

void Theory()
{

  /* Stack allocation */
  // System reserves a block of memory for the program to use as a stack.
  // When these values below are allocated on the stack, the stack pointer moves by order of bytes of the variable type (e.g. 4 bytes for int, 12 bytes for Vector3),
  // so the memory addresses of these variables will be next to each other, in order of their declaration in the code (or reverse).
  // Stack allocation is very fast, but the size of the stack is limited (usually a few MBs), so we can't allocate large amounts of memory on the stack,
  // otherwise we will get a stack overflow (when we exceed the stack size).
  // Everything allocated on the stack is automatically freed when it goes out of scope (e.g. when the function ends), so we don't have to worry about freeing memory allocated on the stack.
  int value = 20;
  int array[5];
  array[0] = 1;
  array[1] = 2;
  array[2] = 3;
  array[3] = 4;
  array[4] = 5;
  Vector3 vector;

  /* Heap allocation */
  // Heap is a large pool of memory that is used for dynamic memory allocation that is also allocated for us. When we ask for more memory on the heap then reserved,
  // the system finds a free block of memory that is large enough to hold the requested size (very expensive).
  // When we allocate memory on the heap, we get a pointer to the allocated memory, and we can use that pointer to access and manipulate the memory.
  // Heap allocation is slower (computationally heavier) than stack allocation, because it involves more complex memory management.
  // Primarily, we want to use stack allocation. Heap allocation is used for long-lived or large variables (e.g. data that needs to persist across
  // function calls or is too large to fit on the stack - textures and such).
  // One workaround may be to pre-allocate large data on the heap and then use it as needed (we would workaround the issue of allocating more memory than available for us),
  // but this is not ideal and can lead to fragmentation and inefficient memory usage.
  // NOTE: `new` keywords is just a operator like +, - etc. and can be overloaded.
  int *hvalue = new int;
  *hvalue = 5;
  int *harray = YoAllocateMe int[5];
  harray[0] = 1;
  harray[1] = 2;
  harray[2] = 3;
  harray[3] = 4;
  harray[4] = 5;
  Vector3 *hvector = new Vector3();
  // new keyword calls malloc behind the scenes to allocate memory on the heap, so following does basically the same thing
  // Only difference is the the code above also calls the constructor of Vector3 to initialize the values, while malloc just allocates raw memory without initializing it (values will be garbage values).
  // But don't do this.
  Vector3 *hvector2 = (Vector3 *)malloc(sizeof(Vector3));
  // this will find a space of memory large enough to hold 50 Vector3 objects in a row (similarly to stack memory). In this case 50 * 3 * 4 (3 floats) = 600 bytes
  Vector3 *hvectorArr = new Vector3[50];

  // this way we can allocate memory for a Vector3 object at a specific memory address (e.g. in the pre-allocated block of memory),
  // but we have to be careful to not overwrite existing data, avoid overflows and to properly free the memory when we're done with it.
  float *ptr = new float[3];               // allocate memory for 3 floats (12 bytes) on the heap and get a pointer to it
  Vector3 *hvector3 = new (ptr) Vector3(); // construct a Vector3 object at the memory address pointed to by ptr

  delete hvalue;       // free the allocated memory for the int
  YoDeleteMe[] harray; // free the allocated memory for the array, use [] because we allocated an array
  delete hvector;      // free the allocated memory for the Vector3
  free(hvector2);      // free the allocated memory for the Vector3. `free` does not call the destructor, `delete` does.
  delete[] hvectorArr; // free the allocated memory for the array of Vector3
  delete ptr;          // free the allocated memory for the float array
  delete hvector3;     // free the allocated memory for the Vector3
}

void DanglingPointer()
{
  Log("---DanglingPointer START---");
  Entity *e;
  {
    // Here we would have to use heap allocation to create an entity that persists after the scope ends - Entity* entity = new Entity("Player")
    Entity entity = Entity("Stack Player");
    e = &entity; // e points to the memory address of entity on the stack
    Log("Entity name: " + entity.GetName());
  }
  // entity goes out of scope here, so the memory address that e points to is now invalid (dangling pointer), and accessing it will lead to undefined behavior (e.g. crash or garbage value).
  Log("Entity name: " + e->GetName());
  Log("---DanglingPointer END---");
}

void HeapAllocation()
{
  Log("---HeapAllocation START---");
  Entity *e;
  {
    // Here we would have to use heap allocation to create an entity that persists after the scope ends - Entity* entity = new Entity("Player")
    Entity *entity = new Entity("Heap Player");
    e = entity; // e points to the memory address of entity on the heap
    Log("Entity name: " + entity->GetName());
  }
  // entity goes out of scope here, so the memory address that e points to is now invalid (dangling pointer), and accessing it will lead to undefined behavior (e.g. crash or garbage value).
  Log("Entity name: " + e->GetName());
  delete e; // free the allocated memory for the entity
  Log("---HeapAllocation END---");
}

void Practice()
{
  DanglingPointer();
  HeapAllocation();

  // Different ways to initialize variables on the stack
  Entity entity;
  Log("Entity name: " + entity.GetName());
  Entity entity2("Player 2");
  Log("Entity name: " + entity2.GetName());
  Entity entity3 = Entity("Player 3");
  Log("Entity name: " + entity3.GetName());
}

void Memory()
{
  LogSectionTitle("Memory");

  Theory();
  Practice();
}