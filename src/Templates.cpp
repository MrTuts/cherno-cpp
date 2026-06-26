#include <string>
#include <array>
#include <iostream>
#include "Log.h"

/* Function overloading. Here the fn body is always the same, only the parametr changes */
static void PrintOverload(int value)
{
  std::cout << value << std::endl;
}
static void PrintOverload(float value)
{
  std::cout << value << std::endl;
}
static void PrintOverload(std::string value)
{
  std::cout << value << std::endl;
}

// Template functions are created during compile time depending on how their our called in our code.
// Once used in our code, the function is created and the generics are replaced with the type used in the call.
// Templates by itself do not exist in the code unless they are called
template <typename T> // <class T> would be the same
static void Print(T value)
{
  std::cout << value << std::endl;
}

namespace
{
  template <typename T, int N> // specifying type of array and size
  class Array
  {
  private:
    T m_Array[N];

  public:
    int GetSize() const
    {
      return N;
    }
  };
}

void Templates()
{
  LogSectionTitle("Templates");

  PrintOverload(5);
  PrintOverload("Hello");
  PrintOverload(5.5f);

  Print(5);
  Print<int>(5); // with specified type
  Print("Hello");
  Print(5.5f);

  Array<int, 5> array;
  Print("Array size: " + std::to_string(array.GetSize()));
  // the std::array is also a template
  std::array<int, 5> array2;
  Print("Array2 size: " + std::to_string(array2.size()));
}