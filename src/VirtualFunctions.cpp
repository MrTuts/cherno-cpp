#include <iostream>
#include <string>
#include "Log.h"

namespace
{
  class Entity
  {
  public:
    // Virtual destructor is important when using virtual functions, it ensures that the correct destructor is called when deleting an object through a base class pointer.
    virtual ~Entity() = default;
    std::string GetName() { return "Entity"; }
    // This enables Method Overriding, it will look at the actual object type instead of the pointer type, it will call the correct function based on the actual object type.
    // Virtual functions cost a little bit of performance and memory because it uses a vtable to look up the function, but it is negligible in most cases and it is worth it for the flexibility it provides.
    virtual std::string GetName2() { return "Entity"; }
  };

  class Player : public Entity
  {
  private:
    std::string m_Name;

  public:
    Player(const std::string &name) : m_Name(name) {}
    std::string GetName() { return m_Name; }
    // the override keyword is optional but it helps to catch errors, it will give a compile-time error if the function does not override a base class function, it is a good practice to use it.
    std::string GetName2() override { return m_Name; }
  };

  /* Interfaces */
  // interfaces are just classes in C++

  class Printable
  {
  public:
    virtual std::string GetClassName() = 0; // pure virtual function, must be implemented by derived classes, makes this class abstract, cannot be instantiated
  };

  class AbstractEntity : public Printable
  {
  public:
    virtual std::string GetName() = 0; // the = 0 makes this function pure virtual, it means that this class cannot be instantiated and any derived class must implement this function.
  };

  class PlayerFromAbstract : public AbstractEntity
  {
  private:
    std::string m_Name;

  public:
    PlayerFromAbstract(const std::string &name) : m_Name(name) {}
    std::string GetName() override { return m_Name; }
    std::string GetClassName() override { return m_Name; }
  };
}

static void PrintName(Entity *entity)
{
  Log("PrintName: " + entity->GetName());
}

void TheProblem()
{
  Log("PROBLEM:");

  Entity *entity = new Entity();
  Log("Should print Entity: " + entity->GetName());
  PrintName(entity);

  Player *player = new Player("Player");
  Log("Should print Player: " + player->GetName());
  PrintName(player);

  // This will call Entity's GetName() instead of Player's GetName(), it looks at the type of the pointer, not the actual object it points to.
  Entity *entityPlayer = player;
  Log("Should print Player: " + entityPlayer->GetName());
  PrintName(entityPlayer);

  delete entity;
  delete player;
}

void TheSolution()
{
  Log("SOLUTION:");
  Player *player = new Player("Player");
  Log("Should print Player: " + player->GetName2());

  Entity *entityPlayer = player;
  Log("Should print Player: " + entityPlayer->GetName2());

  delete player;
}

void InterfacesExamples()
{
  Log("ABSTRACT EXAMPLES:");

  // Not possible to create an instance of an abstract class, because it has pure virtual functions that must be implemented by derived classes.
  // AbstractEntity *abstractEntity = new Player("Abstract Player");
  AbstractEntity *abstractEntity = new PlayerFromAbstract("Abstract Player");
  Log("Should print Abstract Player: " + abstractEntity->GetName());
}

void VirtualFunctions()
{
  LogSectionTitle("Virtual Functions");

  TheProblem();
  TheSolution();

  InterfacesExamples();
}