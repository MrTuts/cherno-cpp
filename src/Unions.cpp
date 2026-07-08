#include "Log.h"
#include <string>
#include <iostream>

namespace
{

  struct Vector2
  {
    float x, y;
  };

  // The goal here is to be able to treat Vector4 as two Vector2s
  struct Vector4
  {
    union // anonymous union. All structs are the same variable
    {
      struct // anonymous struct
      {
        float x, y, z, w;
      };
      struct
      {
        Vector2 a, b; // a = {x,y}; b = {z,w}
      };
    };
  };

  void PrintVector2(const Vector2 &vector)
  {
    std::cout << vector.x << ", " << vector.y << std::endl;
  }
};

// https://www.youtube.com/watch?v=6uqU9Y578n4&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=67
// unions are usefull when we want to have multiple ways to access the same data
// they are quite related to type punning, but unions might be more readable
void Unions()
{
  LogSectionTitle("Unions");

  struct Union
  {
    // union only has one member, both a and b point to the same memory address. They are essentially the same variable
    // size of the union is determined by the largest member. In this case, the size of the union is 8 bytes (size of long)
    union
    {
      long b;
      int a;
    };
  };

  Union u;
  u.a = 2.0f;

  std::cout << u.a << ", " << u.b << std::endl;

  Vector4 vector = {1.0f, 2.0f, 3.0f, 4.0f};
  PrintVector2(vector.a);
  PrintVector2(vector.b);
  vector.z = 500.0f;
  Log("-----------------");
  PrintVector2(vector.a);
  PrintVector2(vector.b);
}