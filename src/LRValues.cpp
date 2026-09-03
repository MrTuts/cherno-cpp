#include "Log.h"
#include <iostream>

// return lvalue
int GetValue()
{
  return 10;
}

// return lvalue reference
int &GetValue2()
{
  static int value = 10;
  return value;
}

// only accepts lvalue
void SetValueLvalue(int value)
{
}

// only accepts lvalue reference
void SetValueLvalueRef(int &value)
{
}

// accepts both lvalue and lvalue reference
void SetValueLvalueAndLvalueRef(const int &value)
{
}

// accepts lvalue
void PrintNameLvalue(std::string &name)
{
  Log(name);
}

// accepts both lvalue and lvalue reference
void PrintNameLvalueAndValueRef(const std::string &name)
{
  Log(name);
}

// accepts only rvalue reference!
void PrintNameRvalueRef(const std::string &&name)
{
  Log(name);
}

/* overloading */
void PrintNameOverload(const std::string &name)
{
  std::cout << "[lvalue] " << name << std::endl;
}
void PrintNameOverload(const std::string &&name)
{
  std::cout << "[rvalue] " << name << std::endl;
}

/*

lvalue - variables that have some kind of storage backing
rvalue - temporary values

RULES
Rule 1) We cannot assign to lvalue
Rule 2) We cannot take an lvalue reference from an rvalue. We can only have an lvalue reference of lvalue
*/
void LRValues()
{
  LogSectionTitle("lvalues rvalues");

  /*
  In this case and in most cases (but not always):
  lvalue - what is on the left side of =
  rvalue - what is on the right side of =
  */
  int i = 10;

  /*
  here "a" and "i" are both lvalue
   */
  int a = i;

  /*
  j is lvalue above
  GetValue return rvalue, it returns an int, which by itself is not stored in memory
  */
  int j = GetValue();
  /* RULE 1 (We cannot assign to lvalue) */
  // GetValue() = 10; This does not make sense, we cannot assign to lvalue to lvalue

  /* GetValue2 is an lvalue reference, which we can assign to */
  GetValue2() = 5;

  /* we can pass both lvalue and rvalue */
  SetValueLvalue(i);
  SetValueLvalue(10);

  /* RULE 2 (We cannot take an lvalue reference from an rvalue) */
  // SetValueLvalueRef(10);
  // int&b = 10;
  // this works, but compiler creates temporary `int temp = 10; const int a& = temp;`
  const int &b = 10;

  SetValueLvalueAndLvalueRef(i);
  SetValueLvalueAndLvalueRef(10);

  // firstName lvalue; "Pavel" rvalue
  std::string firstName = "Pavel";
  // lastName lvalue; "Havel" rvalue
  std::string lastName = "Havel";
  // fullName lvalue; `firstName + lastName` is also rvalue, it is an temporary object
  // temporary string is create from firstName and lastName and then is assigned to fullName
  std::string fullName = firstName + lastName;

  PrintNameLvalue(fullName);
  // does not work, because `firstName + lastName` is rvalue
  // PrintName(firstName + lastName);
  PrintNameLvalueAndValueRef(firstName + lastName); // this works!

  PrintNameRvalueRef(firstName + lastName);
  // PrintNameRvalueRef(firstName); only accepts rvalue

  PrintNameOverload(fullName);
  PrintNameOverload(firstName + lastName);
}