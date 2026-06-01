#include <iostream>
#include <string>
#include "Log.h"

namespace
{
  /* Interfaces */
  // interfaces are just classes in C++

  class Printable
  {
  public:
    virtual std::string GetClassName() = 0; // pure virtual function, must be implemented by derived classes, makes this class abstract, cannot be instantiated
  };

  class AbstractEntity
  {
  public:
    // no need for virtual destructor here, since this class is pure virtual class, which cannot be instantiated, so it cannot be deleted through a base class pointer.
    virtual std::string GetName() = 0; // the = 0 makes this function pure virtual, it means that this class cannot be instantiated and any derived class must implement this function.
  };

  /* Concrete Classes */
  class Entity : public Printable
  {
  public:
    // Virtual destructor is important when using virtual functions, it ensures that the correct destructor is called when deleting an object through a base class pointer.
    virtual ~Entity() = default;
    virtual std::string GetName() { return "Entity"; }
    virtual std::string GetClassName() override { return "Entity Class"; }
  };

  class Player : public Entity
  {
  private:
    std::string m_Name;

  public:
    Player(const std::string &name) : m_Name(name) {}
    std::string GetName() override { return m_Name; }
    virtual std::string GetClassName() override { return "Player Class"; }
  };

  class PlayerFromAbstractEntity : public AbstractEntity
  {
  private:
    std::string m_Name;

  public:
    PlayerFromAbstractEntity(const std::string &name) : m_Name(name) {}
    std::string GetName() override { return m_Name; }
  };
}

static void PrintName(Entity *entity)
{
  Log("Print GetName: " + entity->GetName());
}

static void Print(Printable *obj)
{
  Log("Print GetClassName: " + obj->GetClassName());
}

void Interfaces()
{
  LogSectionTitle("Interfaces");

  Log("ABSTRACT EXAMPLES:");

  // Not possible to create an instance of an abstract class, because it has pure virtual functions that must be implemented by derived classes.
  // AbstractEntity *abstractEntity = new AbstractEntity("Abstract Player");
  // This is possible, since PlayerFromAbstractEntity implements the pure virtual function GetName()
  AbstractEntity *abstractEntity = new PlayerFromAbstractEntity("Abstract Player");
  Log("Should print Abstract Player: " + abstractEntity->GetName());

  Entity *entity = new Entity();
  PrintName(entity);
  Player *player = new Player("Player");
  PrintName(player);

  Print(entity);
  Print(player);

  delete abstractEntity;
  delete entity;
  delete player;
}