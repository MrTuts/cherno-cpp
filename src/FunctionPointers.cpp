#include "Log.h"
#include <string>
#include <vector>
#include <iostream>

static void HelloWorld(int num)
{
  Log("Hello world. The number is " + std::to_string(num));
}

static void PrintValue(int value)
{
  std::cout << "Value: " << value << std::endl;
}

// passing a function as parametr, so the caller decides what to do
static void ForEach(const std::vector<int> &values, void (*func)(int))
{
  for (int value : values)
  {
    func(value);
  }
}

void FunctionPointers()
{
  LogSectionTitle("Function pointers");

  HelloWorld(0);
  // function variable stores the location of instructions in the compiled binary
  // the & is not needed here, but I keep it here
  auto function = &HelloWorld;

  // rewritten the type of function
  void (*fn2)(int); // declare variable
  fn2 = HelloWorld; // assign it

  typedef void (*HelloWorldFunction)(int); // declare the type
  HelloWorldFunction fn3 = HelloWorld;     // declare and assign variable

  function(2);
  fn2(3);
  fn3(5);

  // usefull example
  std::vector<int> values = {1, 5, 4, 2, 3};
  ForEach(values, PrintValue);

  // using lambda function
  // [] is a capture list, we can pass variables from outside here. Well, not in this case because of how the ForEach function parametr is defined
  // (int value) parameters
  // { ... } function body
  ForEach(values, [](int value)
          { std::cout << "Value: " << value << std::endl; });
}