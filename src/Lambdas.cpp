#include "Log.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

// `void(*func)(int)` this function pointer would not accept any capture list
// `const std::function<void(int)> &func` <void(int)> is function that returns void and accepts int parameter
void ForEach(std::vector<int> &values, const std::function<void(int)> &func)
{
  for (int value : values)
  {
    func(value);
  }
}

void Lambdas()
{
  LogSectionTitle("Labmdas");

  std::vector<int> values = {2, 5, 5, 4, 3};
  int a = 5;
  // using lambda function
  // [] is a capture list, we can pass variables from outside here
  // (int value) parameters
  // { ... } function body
  ForEach(values, [&](int value)
          { Log("Value is : " + std::to_string(value) + ", a is: " + std::to_string(a)); });

  auto lambda = [=](int value) mutable
  {
    a = 10;
    Log("Value is : " + std::to_string(value) + ", a is: " + std::to_string(a));
  };

  ForEach(values, lambda);

  // from <algorithm>
  // iterator is a handle to the found element inside the vector, not the element value itself.
  auto iterator = std::find_if(values.begin(), values.end(), [](int value)
                               { return value > 3; });

  // check whether the find_if found some result
  if (iterator == values.end())
  {
    Log("find_if result NOT FOUND");
  }
  else
  {
    // get the index of found element
    // auto index = iterator - values.begin();
    auto index = std::distance(values.begin(), iterator); // better way that also works with std::list etc.

    Log("find_if result: " + std::to_string(*iterator) + ", at position: " + std::to_string(index));
  }
}