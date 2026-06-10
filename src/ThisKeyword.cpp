#include "Log.h"

// we need to declare these here first because of the order they are used in code - EntityC calls PrintEntity and PrintEntity has EntityC in parameters
class EntityC;
static void PrintEntity(EntityC *e);
static void PrintEntity(const EntityC &e);

class EntityC
{
public:
  int x, y;

  EntityC(int x, int y)
  {
    x = x; // this assigns the x to the parameter x (to itself), not the member variable x

    // this is a pointer to the current instance of the class. It is used to access members of the class.
    // EntityC* const e = this; // this is what "this" is under the hood. It is a pointer to the current instance of the class.
    this->x = x;
    // (*this).x = x; other way how to access the member variable x
    this->y = y;

    PrintEntity(this);  // calls (Entity *e)
    PrintEntity(*this); // calls (const Entity &e)
  }

  int GetX() const
  {
    // const Entity* const e = this; // here "this" is defined this way, so we cannot modify the members of the class in this function, because it is a const function
    return this->x;
  }
};

static void PrintEntity(EntityC *e)
{
  Log("Entity:");
  Log("x: " + std::to_string(e->x));
  Log("y: " + std::to_string(e->y));
}
static void PrintEntity(const EntityC &e)
{
  Log("Entity:");
  Log("x: " + std::to_string(e.x));
  Log("y: " + std::to_string(e.y));
}

void ThisKeyword()
{
  LogSectionTitle("This Keyword");

  EntityC e(5, 6);
}
