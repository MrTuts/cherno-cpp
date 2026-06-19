#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include "Log.h"

// pass the return values in function params as references
static void ExampleFn1(const std::string &string, std::string &outRes1, std::string &outRes2)
{
  outRes1 = string.substr(0, 2);
  outRes2 = string.substr(2, 2);
}

// pass the return values in function params as pointers
// allows us to pass nullptrs
static void ExampleFn2(const std::string &string, std::string *outRes1, std::string *outRes2)
{
  // check for nullptr
  if (outRes1)
  {
    *outRes1 = string.substr(0, 2);
  }
  if (outRes2)
  {
    *outRes2 = string.substr(2, 2);
  }
}

// return array of values, there is no mention of array in the return type!
static std::string *ExampleFn3(const std::string &string)
{
  // stack allocated
  std::string res1 = string.substr(0, 2);
  std::string res2 = string.substr(2, 2);
  // copy-constructed into the heap
  return new std::string[]{res1, res2};
}

// return array of values with defined size
static std::array<std::string, 2> ExampleFn4(const std::string &string)
{
  std::string res1 = string.substr(0, 2);
  std::string res2 = string.substr(2, 2);
  std::array<std::string, 2> result;
  result[0] = res1;
  result[1] = res2;
  return result;
}

// return vector of values with defined size
static std::vector<std::string> ExampleFn5(const std::string &string)
{
  std::string res1 = string.substr(0, 2);
  std::string res2 = string.substr(2, 2);
  std::vector<std::string> result(2); // reserve memory space for two items
  result[0] = res1;
  result[1] = res2;
  return result;
}

// tuple is like a class with various variable types, so this allows us to return values with multiple types
static std::tuple<std::string, std::string, int> ExampleFn6(const std::string &string)
{
  std::string res1 = string.substr(0, 2);
  std::string res2 = string.substr(2, 2);

  return std::make_tuple(res1, res2, 10);
}

// using struct

struct FnResult
{
  // we get to name our result vars yaaay
  // we also support multiple return types
  std::string FirstTwoChars;
  std::string SecondTwoChars;
};
static FnResult ExampleFn7(const std::string &string)
{
  std::string res1 = string.substr(0, 2);
  std::string res2 = string.substr(2, 2);

  return {res1, res2};
}

void MultipleReturns()
{
  std::string example1Res1, example1Res2;
  ExampleFn1("Hello", example1Res1, example1Res2);
  Log("Example 1_res1: " + example1Res1 + ", res2: " + example1Res2);

  std::string example2Res1;
  ExampleFn2("Blue", &example2Res1, nullptr); // we can pass nullptr, we might not care about this parameter
  Log("Example 2_res1: " + example2Res1 + ", res2 is unused");

  // we get array as result, but it's not clear what is the size of the result
  std::string *example3Res = ExampleFn3("Green");
  Log("Example 3_res1: " + example3Res[0] + ", res2: " + example3Res[1]);
  // result is heap allocated, so we must delete, but the function signature itself does not give us this info!
  // From the signature, we do not event know whether we need to delete or delete[]
  delete[] example3Res;

  // we get array as result with known size
  std::array<std::string, 2> example4Res = ExampleFn4("Yellow");
  Log("Example 4_res1: " + example4Res[0] + ", res2: " + example4Res[1]);

  // we get vector with unknown size
  std::vector<std::string> example5Res = ExampleFn5("Black");
  Log("Example 5_res1: " + example5Res[0] + ", res2: " + example5Res[1]);

  std::tuple<std::string, std::string, int> example6Res = ExampleFn6("Brown");
  Log("Example 6_res1: " + std::get<0>(example6Res) + ", res2: " + std::get<1>(example6Res) + ", res3: " + std::to_string(std::get<2>(example6Res)));

  // Tha BEST
  FnResult example7Res = ExampleFn7("Pink");
  Log("Example 7_res1: " + example7Res.FirstTwoChars + ", res2: " + example7Res.SecondTwoChars);
}