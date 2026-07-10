#include "Log.h"
#include <iostream>

namespace
{
  class Base
  {
  public:
    Base()
    {
    }
    // always declare destructor as virtual if the class is meant to be extended
    virtual ~Base()
    {
    }
  };

  class Derived : public Base
  {
  public:
    Derived()
    {
    }
    ~Derived()
    {
    }
  };

  class AnotherDerived : public Base
  {
  public:
    AnotherDerived()
    {
    }
    ~AnotherDerived()
    {
    }
  };
}

// https://www.youtube.com/watch?v=pWZS1MtxI-A&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=69
void TypeCasting()
{
  LogSectionTitle("Type casting");

  int value = 5;
  double a = value;         // implicit conversion of int into double
  double b = (double)value; // explicit conversion. "C style case"
  /* C style casts  will attempt every cast type until one works, meaning the result won’t necessarily be what we expect */

  /* ----- Static cast ----- */
  /*
    Is used for compile-time type checking and conversion between compatible types.
    It is safer than C-style casts, as it performs additional checks during compilation to ensure that the conversion is valid.
  */

  double c = static_cast<int>(value); // C++ style cast
  /*
    C++ style casts might do some additional checks whether the type can be converted (during runtime or compilation),
    but they basically do the same thing as C style cast.
    They are good in a wat that we find any casts we do in our code by simple search.
  */

  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;
  std::cout << "c: " << c << std::endl;

  /* ----- Const cast ----- */
  /*
    Is used to add or remove the const qualifier from a variable.
    It allows you to modify a variable that was originally declared as const, but it should be used with caution.
    It can be used only with reference, pointer-to-object, or pointer-to-data-member types. It cannot be used with fundamental types like int, float, etc.
  */
  int i = 5;
  std::cout << "i: " << i << std::endl;
  const int &iRef = i;
  const int *iPtr = &i;
  const_cast<int &>(iRef) = 6;
  std::cout << "i after const_cast<int &>: " << i << std::endl;
  *const_cast<int *>(iPtr) = 8;
  std::cout << "i after *const_cast<int *>(iPtr): " << i << std::endl;

  // this code will compile and run, we won't receive any errors, but the iConst will never change it's value, it's a silent error!
  const int iConst = 5;
  std::cout << "iConst: " << iConst << std::endl;
  const int &iConstRef = iConst;
  const int *iConstPtr = &iConst;
  const_cast<int &>(iConstRef) = 6;
  std::cout << "iConst after const_cast<int &>: " << iConst << std::endl;
  *const_cast<int *>(iConstPtr) = 8;
  std::cout << "iConst after *const_cast<int *>(iPtr): " << iConst << std::endl;

  /* ------ Reinterpret case ------ */
  /*
    Is used for low-level type conversions, such as converting between unrelated pointer types or between pointer and integer types.
    It does not perform any safety checks and should be used with caution, as it can lead to undefined behavior if used incorrectly.
    "I don't want to actually convert anything, I just want to interpret it as something else"
    Basically Everything done in TypePunning.cpp
  */
  // AnotherDerived *d = static_cast<AnotherDerived *>(&value); // this won't work
  AnotherDerived *d1 = (AnotherDerived *)&value;                   // C style cast
  AnotherDerived *d2 = reinterpret_cast<AnotherDerived *>(&value); // this works

  /* ------ Dynamic cast ------ */
  /*
    Is used for safe downcasting in an inheritance hierarchy.
    It checks at runtime if the cast is valid and returns nullptr if it is not.
    It requires the base class to have at least one virtual function (usually a virtual destructor) to work properly.
  */

  Derived *derived = new Derived();
  Base *base = derived;
  // Derived and AnotherDerived both inherit from Base, but the var itself is a Derived class, so it can't be
  // cast to AnotherDerived. This dynamic_cast checks for that and will return nullptr in this case
  AnotherDerived *ac = dynamic_cast<AnotherDerived *>(base);
  if (!ac)
  {
    Log("base cannot be converted into AnotherDerived class. Meaning it is not an instance of AnotherDerived");
  }
  if (ac)
  {
    Log("base can be converted into AnotherDerived class. Meaning it is an instance of AnotherDerived");
  }
}