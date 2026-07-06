#include "Log.h"
#include <string>
#include <functional>

namespace apple
{
  namespace functions
  {
    void Print(const char *text)
    {
      Log(text);
    }
  }

  class Entity
  {

  private:
    float m_x;

  public:
    Entity(float x) : m_x(x) {}

    float GetX() const
    {
      return m_x;
    }
  };
}

namespace orange
{
  void Print(const char *text)
  {
    std::string temp = text;
    std::reverse(temp.begin(), temp.end());
    Log(temp);
  }
}

// https://www.youtube.com/watch?v=ts1Eek5w7ZA&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=61
void Namespaces()
{
  LogSectionTitle("Namespaces");

  apple::functions::Print("Hello");
  orange::Print("Hello");

  using namespace orange;
  Print("Hello");

  // alias for namespace
  namespace appleFunction = apple::functions;
  appleFunction::Print("Hello");

  apple::Entity e{0.1f};
  // pointer to a member function
  auto getXFn = &apple::Entity::GetX;
  // calling GetX through the pointer to member function
  float x2 = (e.*getXFn)();
  Log(std::to_string(e.GetX()));
  Log(std::to_string(x2));

  // where we could possibly use this approach, we invoke a function pointer, which is a member function of a class, and we want to call it on an object of that class.
  // std::invoke is a utility that allows us to call the member function on the object without having to use the pointer-to-member syntax directly.
  // It can be particularly useful in generic programming where we might not know the exact type of the object at compile time.
  float x3 = std::invoke(&apple::Entity::GetX, e);
  Log(std::to_string(x3));
}