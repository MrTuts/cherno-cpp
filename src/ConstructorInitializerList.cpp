#include <string>
#include "Log.h"

namespace
{
  class Example
  {
  public:
    Example()
    {
      Log("Created Entity");
    };
    Example(int X)
    {
      Log("Created Entity with " + std::to_string(X));
    };
  };

  class Entity
  {
  private:
    std::string m_Name;
    int m_Score;
    Example m_Example;

  public:
    // values will be defined in the order they are declared in the class, not in the order they are listed in the initializer list
    // so here m_Name will be initialized before m_Score, even though m_Score is listed first in the initializer list
    Entity()
        : m_Score(0),
          m_Name("Unknown"),
          m_Example(Example(4)) // we can pass 4 or Example(4), does not change anything
    {
      // called after the members have been initialized
      Init();
    }
    Entity(const std::string &name)
        : m_Score(0),
          m_Name(name),
          m_Example(4) // we can pass 4 or Example(4), does not change anything
    {
      Init();
    }
    Entity(std::string name, int score)
        : m_Score(score)
    {
      // this is less efficient than initializing m_Name in the initializer list,
      // this would cause the m_name to be constructed by default constructor and then
      // again here, because what would happen here is m_name = std::string(name) and the original std::string would be just thrown away
      m_Name = name;
      m_Example = Example(8);
      Init();
    }

    void Init()
    {
    }
    // "Classic" way of initializing members in the constructor body, this is less efficient than using an initializer list,
    // because it tve value is constructed twice, first with the default constructor and then with the assignment operator,
    // this is especially inefficient for complex types like std::string
    // Entity()
    // {
    //   m_Name = "Unknown";
    //   m_Score = 0;
    //   Init();
    // }

    // Entity(const std::string &name)
    // {
    //   m_Name = name;
    //   Init();
    // }

    const std::string &GetName() const
    {
      return m_Name;
    }
  };

}

void ConstructorInitializerList()
{
  Entity e0;
  Log("Default constructor: " + e0.GetName());
  Entity e1("Entity1");
  Log("Parameterized constructor: " + e1.GetName());

  Entity e2("Entity1", 10); // Created Example class twice! Because of the way we initialize m_Example in the constructor body
}