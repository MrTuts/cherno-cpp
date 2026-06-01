#include "Log.h"

namespace
{
  class Entity
  {
  public:
    float x, y;

    void Move(float xDir, float yDir)
    {
      x += xDir;
      y += yDir;
    };
  };

  class Player : public Entity
  {
  public:
    const char *Name;

    void PrintName()
    {
      Log(Name);
    }
  };
}

void Inheritance()
{
  LogSectionTitle("Inheritance");

  Log("Size of Entity:");
  Log(sizeof(Entity)); // hase 2 floats, so 8 bytes (4 bytes for each float)
  Log("Size of Player:");
  Log(sizeof(Player)); // has 2 floats from Entity (8 bytes) and a pointer to char (8 bytes on 64-bit system), so total 16 bytes.

  Player player;
  player.Name = "Pavel";
  player.x = 0;
  player.y = 0;

  player.Move(1, -1); // move right
  player.PrintName();
}