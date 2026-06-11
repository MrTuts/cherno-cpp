#include "Log.h"
#include <memory> // for std::unique_ptr, std::shared_ptr, std::weak_ptr
#include <string> // for std::string

namespace
{
  class Entity
  {
  private:
    std::string m_name;

  public:
    Entity(const std::string &name) : m_name(name)
    {
      Log("Created Entity! " + m_name);
    }
    ~Entity()
    {
      Log("Destroyed Entity! " + m_name);
    }

    void Print() {}
  };
}

void SmartPointers()
{
  LogSectionTitle("Smart Pointers");

  // std:unique_ptr is a scoped pointer - when it goes out of scope, it automatically deletes the memory it owns.
  // Unique pointer cannot be copied, they would point at the same memory address, so the copy would point to deleted point of memory
  {
    // preferred way to create a unique_ptr, it is exception safe:
    //     if the constructor of Entity throws an exception, the memory will be automatically cleaned up, preventing memory leaks
    std::unique_ptr<Entity> entity1 = std::make_unique<Entity>("Entity1");
    // also possible, but not exception safe, if the constructor of Entity throws an exception, the memory will not be cleaned up, leading to a memory leak
    std::unique_ptr<Entity> entity2(new Entity("Entity2"));
    // This is not allowed, constructor is explicit, so we cannot do implicit conversion from Entity* to std::unique_ptr<Entity>
    // std::unique_ptr<Entity> entity1 = new Entity();

    // error: cannot copy unique_ptr, fails at compile time, because the copy constructor is deleted to prevent copying
    // std::unique_ptr<Entity> entity3 = entity1;

    Entity *entityPtr1 = new Entity("Entity3");
    // if std::make_unique is not used, we would get double delete here, since entity3 and 4 do not know of each other.
    std::unique_ptr<Entity> entity3(entityPtr1);
    // std::unique_ptr<Entity> entity4(entity); // this would cause a double delete, crashing the program
  }

  std::weak_ptr<Entity> entityWeak;
  {
    std::shared_ptr<Entity> entity0;
    {
      std::shared_ptr<Entity> entity1 = std::make_shared<Entity>("Entity1");
      // we don't want to do that because std::make_shared needs to create a block for pointer counting.
      //     It constructs the Entity and the control block in a single allocation, which is more efficient than creating them separately.
      //     but weak_ptr will keep the control block and resource from being freed
      // Constructing this way it creates two separate allocations: one for the Entity and one for the control block, which is less efficient.
      // std::shared_ptr<Entity> entity2(new Entity("Entity1"));

      entity0 = entity1;    // shared ownership, both entity0 and entity1 point to the same Entity, reference count is 2
      entityWeak = entity1; // weak pointer, does not increase reference count, it can be used to check if the Entity still exists without owning it
    }
    // entity1 goes out of scope, reference count decreases to 1, but the Entity is not destroyed because entity0 still owns it, so the Entity is not destroyed yet
  }
  // entity0 goes out of scope, reference count decreases to 0, the Entity is destroyed because there are no more owners
  // But the weak_ptr will still keep the control block and resource from being freed, so we can check if the Entity still exists using the weak_ptr
}