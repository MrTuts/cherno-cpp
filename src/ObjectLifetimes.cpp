#include "Log.h"

static int *CreateArrayWrong()
{
  int array[50]; // allocated on the stack
  return array;  // returning pointer to local variable. This is a bug. The caller will get a pointer to memory that has been deallocated.
}

static int *CreateArrayRight()
{
  int *array = new int[50]; // allocated on the heap
  return array;             // returning pointer to heap memory. The caller is responsible for deleting it.
}

static void FillArray(int *array)
{
  for (int i = 0; i < 50; i++)
  {
    array[i] = i;
  }
}

namespace
{
  class Entity
  {
  public:
    Entity()
    {
      Log("Entity created");
    }
    ~Entity()
    {
      Log("Entity destroyed");
    }
  };

  class ScopedPtr
  {
  private:
    Entity *m_Ptr;

  public:
    ScopedPtr(Entity *ptr) : m_Ptr(ptr) {}
    ~ScopedPtr() { delete m_Ptr; }
  };
}

void ObjectLifetimes()
{
  LogSectionTitle("Object Lifetimes");
  {
    Entity e1; // created on the stack. Automatically destroyed when going out of scope.

    // created on the heap. Automatically destroyed when ePtr goes out of scope.
    // so this will automatically clean up the memory when we leave this scope, preventing memory leaks!
    ScopedPtr ePtr = new Entity(); // implicit conversion from Entity* to ScopedPtr, same as `ScopedPtr ePtr(new Entity())`
  }

  int *array1 = CreateArrayWrong(); // This will lead to undefined behavior if we try to use array1
  int *array2 = CreateArrayRight(); // This is ok
  int array3[50];                   // This is ok, but only within the scope of this function
  FillArray(array3);                // This is ok
}