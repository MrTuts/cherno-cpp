#include <iostream>
#include <string>
#include "Log.h"

struct Vector2
{
  float x, y;

  Vector2(float x, float y) : x(x), y(y) {}

  Vector2 Add(const Vector2 &other) const
  {
    return Vector2(x + other.x, y + other.y);
  }

  Vector2 operator+(const Vector2 &other) const
  {
    return Add(other);
  }

  Vector2 Multiply(const Vector2 &other) const
  {
    // This demonstrates how to call the operator* function defined below
    // instead of calling Multiply from operator* function, like we do in Add
    return operator*(other);
    // return *this * other; another way how to call operator* function defined below
  }

  Vector2 operator*(const Vector2 &other) const
  {
    return Vector2(x * other.x, y * other.y);
  }

  // In Java would have to override equals() method, but in C++ we can just overload the == operator
  bool operator==(const Vector2 &other) const
  {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Vector2 &other) const
  {
    return !(*this == other);
    // return !operator==(other);
  }
};

// overloading << operator for Vector2, so we can print it with std::cout
// the `(std::ostream &stream)` is the existing class, in this case ostream
// In Java we would have to create a function like `toString()` in Vector2 class
std::ostream &operator<<(std::ostream &stream, const Vector2 &vector)
{
  stream << "(x: " << vector.x << ", y: " << vector.y << ")";
  return stream;
}

// Operators are just functions
void Operators()
{
  LogSectionTitle("Operators");

  // This is Java like solution
  Vector2 position1(5.0f, 4.0f);
  Vector2 speed1(.5f, 1.5f);
  Vector2 powerUp1(1.1f, 1.1f);
  Vector2 result1 = position1.Add(speed1.Multiply(powerUp1));
  Log("Result 1: (x: " + std::to_string(result1.x) + ", y: " + std::to_string(result1.y) + ")");

  // This is C++ like solution
  Vector2 position2(5.0f, 4.0f);
  Vector2 speed2(.5f, 1.5f);
  Vector2 powerUp2(1.1f, 1.1f);
  Vector2 result2 = position2 + speed2 * powerUp2;
  Log("Result 2: (x: " + std::to_string(result2.x) + ", y: " + std::to_string(result2.y) + ")");

  Log(result1 == result2 ? "Results are the same" : "Results are different");
  Log(result1 != result2 ? "Results do differ" : "Results do not differ");

  // << is also a operator, which cout overloads. This does not work by default, because there is no overload for Vector2.
  // It does work here, because we defined it above. This is a very common way to print custom types in C++.
  std::cout << result2 << std::endl;
}