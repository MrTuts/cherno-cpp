// https://www.youtube.com/watch?v=BvR1Pgzzr38&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=44
#include <iostream>
#include <string>
#include "Log.h"

namespace
{
  struct Vector2
  {
    float x, y;
  };

  class String
  {
  private:
    char *m_Buffer;
    unsigned int m_Size;

  public:
    String(const char *string)
    {
      m_Size = strlen(string);
      m_Buffer = new char[m_Size + 1]; // we could also use strcpy; +1 for null termination character
      // this line copies string into m_Buffer, we could also do it as below
      // we could also write `m_Size+1`, but we can't be sure the string was constructed correctly with null termination character
      memcpy(m_Buffer, string, m_Size);
      // for (int i = 0; i < m_Size; i++)
      // {
      //   m_Buffer[i] = string[i];
      // }
      m_Buffer[m_Size] = 0; // ensure we have null termination character
    }

    // Copy constructor - accepts its own class in the constructor
    // String(const String &other) = delete // this would disable copying if this class cannot be copied
    String(const String &other) : m_Size(other.m_Size)
    {
      Log("Copied string");
      m_Buffer = new char[m_Size + 1];
      memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }

    ~String()
    {
      delete[] m_Buffer;
    }

    char &operator[](unsigned int index)
    {
      // should do index checking
      return m_Buffer[index];
    }

    // this enables us to access the private members of String in the operator<< function
    friend std::ostream &operator<<(std::ostream &stream, const String &string);
  };

  // overloading << operator for String, so we can print it with std::cout
  std::ostream &operator<<(std::ostream &stream, const String &string)
  {
    stream << string.m_Buffer;
    return stream;
  }
}

void Copying()
{
  LogSectionTitle("Copying");

  int a = 2;
  int b = a; // copy assignment. Copies the value of a into b. a and b are independent variables.
  b = 3;     // changing b does not change a
  Log("a:" + std::to_string(a) + ", b:" + std::to_string(b));

  Vector2 v1{1.0f, 2.0f};
  Vector2 v2 = v1; // copy assignment. Copies the value of v1
  v2.x = 3.0f;     // changing v2 does not change v1
  Log("v1:(" + std::to_string(v1.x) + ", " + std::to_string(v1.y) + "), v2:(" + std::to_string(v2.x) + ", " + std::to_string(v2.y) + ")");

  Vector2 *v1Ptr = new Vector2{1.0f, 2.0f};
  Vector2 *v2Ptr = v1Ptr; // copy assignment. Copies the pointer, not the value
  v2Ptr->x = 3.0f;        // changing v2Ptr changes v1Ptr
  Log("v1Ptr:(" + std::to_string(v1Ptr->x) + ", " + std::to_string(v1Ptr->y) + "), v2Ptr:(" + std::to_string(v2Ptr->x) + ", " + std::to_string(v2Ptr->y) + ")");

  delete v1Ptr;

  String string = "Pavel";
  // The String class contains m_Buffer pointer, copying would just do a "shallow copy" by copying the pointer, leading to two objects pointing at the same block of memory
  // After the String is destructed and m_Buffer destroys, this would crash (double destroy)
  // We need to copy the m_Buffer memory block - we need to do a deep copy - we need a copy constructor
  String second = string;

  // we can do this thanks to overloading [] operator
  second[2] = 'r';

  std::cout << string << std::endl;
  std::cout << second << std::endl;
}