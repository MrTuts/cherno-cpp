#include "Log.h"
#include <string>

namespace
{
  class Entity
  {
  public:
    void Print() const
    {
      Log("Hello");
    }
  };

  class ScopedPtr
  {
  private:
    Entity *m_Obj;

  public:
    ScopedPtr(Entity *entity) : m_Obj(entity)
    {
    }

    ~ScopedPtr()
    {
      Log("Deleted");
      delete m_Obj;
    }

    // overload the arrow operator to return the pointer to Entity, so we can call fn on it
    const Entity *operator->() const
    {
      return m_Obj;
    }
  };

  struct Vector3
  {
    float x, y, z;
  };
}

void ArrowOperator()
{
  Entity e;
  e.Print();

  Entity *ptr = &e; // pointer to Entity, points to e

  Entity &entity = *ptr; // dereference ptr and assign it to entity
  entity.Print();        // call fn

  (*ptr).Print(); // dereference ptr and call fn, same as above

  ptr->Print(); // this is the same as (*ptr).Print(), but more concise, this is called the arrow operator

  const ScopedPtr entity2 = new Entity();
  entity2->Print(); // we can access Print because we are overloading the arrow operator

  // get the offset in memory of a class variable. The offset is defined by the order they are defined in the class
  // - cast 0 (nullptr) into Vector3 pointer;
  // - access x(y,z);
  // - take the memory address of variable (&); this gives as the offset, because we are starting from 0. We used the arrow operator to give us the offset value
  // - cast it to size_t (int/long depending on the system)
  size_t offsetX = (size_t)&((Vector3 *)0)->x;
  size_t offsetY = (size_t)&((Vector3 *)nullptr)->y;
  size_t offsetZ = (size_t)&((Vector3 *)0)->z;

  Log("offsetX: " + std::to_string(offsetX) + "; offsetY: " + std::to_string(offsetY) + "; offsetZ: " + std::to_string(offsetZ));
}