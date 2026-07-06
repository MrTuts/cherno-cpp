#include <iostream>
#include "Log.h"

int g_Variable = 5;        // global variable, prefix g_ for global variables
static int s_Variable = 5; // can't be accessed outside of this translation unit (file) due to internal linkage

// Make structs or classes private to this translation unit (file) by putting them in an unnamed namespace,
// this is a common practice to avoid name conflicts and to indicate that they are only used in this file.
namespace
{
  struct Entity
  {
    int x, y;

    void Print()
    {
      std::cout << "X: " << x << ", Y: " << y << std::endl;
    };

    // Static member function that can access static members but not non-static members
    static void PrintStatic(Entity &e)
    {
      std::cout << "X: " << e.x << ", Y: " << e.y << std::endl;
    };
  };

  struct EntityStat
  {
    static int x, y;

    void Print()
    {
      std::cout << "X: " << x << ", Y: " << y << std::endl;
    };
  };

  class Singleton
  {
  private:
    static Singleton *s_Instance;

  public:
    static Singleton &Get()
    {
      return *s_Instance;
    }

    void Hello()
    {
      std::cout << "Hello from Singleton" << std::endl;
    }
  };
  // declare the static member variable of the Singleton class, it must be defined outside of the class definition
  Singleton *Singleton::s_Instance = nullptr;

  // using static to create singleton class
  class Singleton2
  {
  public:
    static Singleton2 &Get()
    {
      static Singleton2 instance;
      return instance;
    }

    void Hello()
    {
      std::cout << "Hello from Singleton2" << std::endl;
    }
  };
}

static void Function()
{
  // when this function is called for the first time, it will be initialized to 0
  // when called any other time, the value won't initialize again
  static int i = 0;
  Log("i: " + std::to_string(i));
  i++;
}

// WE NEED TO DEFINE STATIC MEMBERS OUTSIDE OF THE CLASS DEFINITION
int EntityStat::x;
int EntityStat::y;

void StaticFn()
{
  LogSectionTitle("Static");
  Entity entity;
  entity.x = 2;
  entity.y = 3;

  Entity entity2 = {4, 5}; // aggregate initialization

  entity.Print();
  entity2.Print();

  Log("    Modifying static variables:");
  /* Modifies static variables using class instances */
  EntityStat entityStat;
  entityStat.x = 10;
  entityStat.y = 20;
  EntityStat entityStat2; // Cannot use aggregate initialization sice static members are not part of the object instance
  entityStat2.x = 5;
  entityStat2.y = 10;

  // Modifying static variable using class name and scope resolution operator
  EntityStat::x = 15;
  EntityStat::y = 25;

  entityStat.Print();
  entityStat2.Print();

  LogSectionTitle("Static function");
  Function();
  Function();
  Function();

  Singleton::Get().Hello();
  Singleton2::Get().Hello();
}