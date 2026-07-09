#include "Log.h"

namespace
{
  class Base
  {
  public:
    Base()
    {
      Log("Base Constructor");
    }
    // always declare destructor as virtual if the class is meant to be extended
    virtual ~Base()
    {
      Log("Base Destructor");
    }
  };

  class Derived : public Base
  {
  private:
    int *m_Array;

  public:
    Derived()
    {
      m_Array = new int[5];
      Log("Derived Constructor");
    }
    ~Derived()
    {
      delete m_Array;
      Log("Derived Destructor");
    }
  };
}

// https://www.youtube.com/watch?v=jELbKhGkEi0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=68
void VirtualDestructors()
{
  LogSectionTitle("Virtual destructors");

  Base *base = new Base();
  delete base;

  Log("------------------");

  Derived *derived = new Derived();
  delete derived;

  Log("------------------");

  Base *poly = new Derived();
  // Only base destructor is called! Unless the Base destructor is marked as virtual
  delete poly;
}