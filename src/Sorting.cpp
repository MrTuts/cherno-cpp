#include "Log.h"
#include <vector>
#include <algorithm> // where sort is
#include <functional>

static void LogVector(std::vector<int> &vec)
{
  for (int value : vec)
  {
    Log(value);
  }
}

void Sorting()
{
  LogSectionTitle("Sorting");

  std::vector<int> values = {3, 5, 1, 4, 2};

  std::sort(values.begin(), values.end()); // sorts in ascending order by default
  LogVector(values);
  Log("---");

  std::sort(values.begin(), values.end(), std::greater<int>()); // sorts in descending
  LogVector(values);
  Log("---");

  std::sort(values.begin(), values.end(), [](int a, int b)
            { return a < b; });
  LogVector(values);
  Log("---");

  // sort 1 to the end of array
  std::sort(values.begin(), values.end(), [](int a, int b)
            { if(a ==1){
              return false;
            }
            if(b ==1){
              return true;
            } 
            return a<b; });
  LogVector(values);
}