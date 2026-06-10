#include <iostream>
#include <string>
#include "Log.h"

namespace
{
  class Entity
  {
  private:
    std::string m_Name;
    int m_Age;

  public:
    Entity(const std::string &name) : m_Name(name), m_Age(-1) {}
    // explicit disables calling this constructor with implicit conversions, so we cannot do Entity b = 30; but we can still do Entity b(30); or Entity b = (Entity)30;
    explicit Entity(int age) : m_Name("Unknown"), m_Age(age) {}
    std::string GetName() const { return m_Name; }
    int GetAge() const { return m_Age; }
  };
}

void PrintEntity(const Entity &entity)
{
  Log("Entity name: " + entity.GetName() + ", age: " + std::to_string(entity.GetAge()));
}

void ImplicitExplicit()
{
  LogSectionTitle("Implicit and Explicit Constructors");

  Entity a0("Alice");
  Entity b0(30);

  Entity a1 = Entity("Alice");
  Entity b1 = Entity(30);

  // these work because we have constructors that can be called with a single argument, so the compiler can implicitly convert the string "Bob" to an Entity and the int 25 to an Entity
  Entity a2 = std::string("Bob"); // implicit conversion from std::string, then to Entity
  // Entity b2 = 25;                 // implicit conversion from int to Entity, this is NOT allowed, because the constructor is marked as explicit
  Entity b2 = (Entity)25; // Casting to Entity type, this is allowed

  // PrintEntity(22);                     // implicit conversion from int to Entity, this is NOT allowed, because the constructor is marked as explicit
  PrintEntity(std::string("Charlie")); // implicit conversion from std::string to Entity, this is allowed
}