#include <array>
#include "Log.h"

template <typename T, size_t SIZE>
static void PrintArray(std::array<T, SIZE> &data)
{
  for (size_t i = 0; i < data.size(); i++)
  {
    Log("data at " + std::to_string(i) + " is " + std::to_string(data[i]));
  }
}

// static in term of not changing size
void StaticArrays()
{
  // arrays are stored on stack
  std::array<int, 5> data = {5, 10, 15, 20, 25};
  PrintArray<int, 5>(data);

  int dataOld[5];
  // dataOld[5] = 2; // Overflow! Nothing will stop us from doing this
  data[5] = 2; // std::array has bounds checking - optionally, during debug
}
