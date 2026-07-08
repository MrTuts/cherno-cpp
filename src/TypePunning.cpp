#include "Log.h"
#include <string>

namespace
{
  struct Entity
  {
    int x, y;

    int *GetPositions()
    {
      // returning the memory address of x means we can treat it as and array
      // does not create any new array (would be needed to be on heap)
      return &x;
    }
  };
}

// https://www.youtube.com/watch?v=8egZ_5GA9Bc&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=66
void TypePunning()
{
  LogSectionTitle("Type punning");

  int a = 50;
  double value = a; // converts int into double implicitly

  // This treats the int value as double, does not convert int into double
  // this is not something we want to do, this double will grab memory pass the int, which was not allocated for the int
  // and can be whatever. Manipulating could manipulate bytes allocated to another value, possibly leading to crash
  double value2 = *(double *)&a; // take address of a, convert it to double pointer and dereference it
  // same as above, but does not create a copy of a
  double &value3 = *(double *)&a;

  Log("value: " + std::to_string(value));
  Log("value2: " + std::to_string(value2));
  Log("value3: " + std::to_string(value3));

  Entity e{5, 8};

  // normal way of accessing struct variables
  int x = e.x;
  // treating entity as array of ints.
  // This is valid since Entity struct has only int x,y values, which in memory would be stored the same as
  // int array of size 2
  int *position = (int *)&e;
  Log("position[0]: " + std::to_string(position[0]));
  Log("position[1]: " + std::to_string(position[1]));

  // &e:        take address of e
  // (char *)   cast it to a char pointer (1 byte)
  // (... +4)   add 4 bytes - this moves 4 bytes to right, pointing at y value
  // (int *)    cast it to int pointer
  // *(...)     dereference the int pointer
  int y = *(int *)((char *)&e + 4);
  Log("y: " + std::to_string(position[1]));

  int *positions = e.GetPositions();
  Log("positions[0]: " + std::to_string(positions[0]));
  Log("positions[1]: " + std::to_string(positions[1]));
}