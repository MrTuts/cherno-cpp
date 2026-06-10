#include <string>
#include "Log.h"

/* Look at Consts.cpp for more */
namespace
{
  class Entity
  {
  private:
    std::string m_name;
    mutable int m_debugCount = 0; // allows us to modify m_debugCount even in const methods
  public:
    const std::string &GetName() const
    {
      m_debugCount++; // we can modify mutable members in const methods
      return m_name;
    }

    const std::string &GetName2()
    {
      m_debugCount++; // we can modify mutable members in const methods
      return m_name;
    }
  };
}

void Mutables()
{
  LogSectionTitle("Mutables");
  const Entity e;
  std::string eName = e.GetName();
  // e.GetName2(); // we cannot call non-const method on const object

  /* Lambda function */
  int x = 7;
  x++;
  auto f1 = []()
  {
    // Log("Lambda with mutable:" + std::to_string(x)); // error: cannot capture x because it is not in scope
    Log("f1: cannot access x"); // error: cannot capture x because it is not in scope
  };
  // we need to capture x in order to use it inside the lambda. We can capture it by value or by reference.
  // capture x by value
  // auto f = [x]()
  // this captures every value used inside the lambda by value
  // auto f = [=]()
  // this captures every value used inside the lambda by reference
  // auto f = [&]()
  // capture x by reference,
  auto f2 = [&x]()
  {
    x++; // this does modify the original x outside the lambda, because we captured x by reference
    Log("f2:" + std::to_string(x));
  };

  auto f3 = [=]()
  {
    // x++; ERROR: cannot modify x because it is captured by value
    // we'd need to e.g.
    int y = x;
    y++;
    Log("f3:" + std::to_string(y));
  };

  auto f4 = [=]() mutable
  {
    // we can modify x because we marked the lambda as mutable, this does NOT affect the original x outside the lambda
    // it creates new copy of x that we can modify inside the lambda, similar to what we did in f2
    x++;
    Log("f4:" + std::to_string(x));
  };

  Log("x before:" + std::to_string(x));
  f1();
  f2();
  // The x copied into these function will still have value 8, even thought f2 changes x to 9.
  // The copy of x in f3 and f4 is created when the lambda is defined, which is before the f2 is called, so it captures the value of x at that time, which is 8.
  // If we moved f2() call before the lambda definitions, then the captured value of x in f3 and f4 would be 9
  Log("x after f2: " + std::to_string(x));
  f3();
  Log("x after f3: " + std::to_string(x));
  f4();
  Log("x after f4: " + std::to_string(x));
}