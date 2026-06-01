#include "Log.h"

struct Entity
{
  // can only be accessed by the class itself, not by derived classes or outside code
private:
  int x, y;

  void Print()
  {
  }

  // can be accessed by the class itself and by derived classes, but not by outside code
protected:
  int health;

  // can be accessed everywhere
public:
  Entity() : x(0), y(0), health(100) {}
};

class Player : public Entity
{
public:
  Player()
  {
    // this->x = 10; // error: 'int Entity::x' is private within this context
    // this->Print(); // error: 'void Entity::Print()' is private within this context

    this->health = 80; // this is fine, because health is protected, so it can be accessed by derived classes
  }
};

// passing private here means that outside code cannot treat Player as an Entity.
class PlayerPrivate : private Entity
{
};

void Visibility()
{
  Entity e;
  // e.x = 10; // error: 'int Entity::x' is private within this context
  // e.Print(); // error: 'void Entity::Print()' is private within this context
  // e.health = 80; // error: 'int Entity::health' is protected within this context

  Entity *playerEnt = new Player;

  // Entity *playerPrivateEnt = new PlayerPrivate; // this is not possible, because PlayerPrivate inherits from Entity privately
}