#include <iostream>
#include "Log.h"

// declarations
void Conditions();
void Loops();
void Pointers();
void References();
void ClassesAndStructs();
void StaticFn();
void Enums();
void Inheritance();
void Memory();
void VirtualFunctions();
void Interfaces();
void Visibility();
void Arrays();
void Strings();
void Consts();
void Mutables();
void ConstructorInitializerList();
void TernaryOperators();
void ImplicitExplicit();
void Operators();
void ThisKeyword();
void ObjectLifetimes();
void SmartPointers();
void Copying();
void ArrowOperator();
void DynamicArrays();
void DynamicArraysOptimizations();

extern int g_Variable; // external linkage. Links to g_Variable defined in Static.cpp

int main()
{
  // Conditions();
  // Loops();
  // Pointers();
  // References();
  // ClassesAndStructs();
  // Enums();
  // Inheritance();
  // Memory();
  // VirtualFunctions();
  // Interfaces();
  // Visibility();
  // Arrays();
  // Strings();
  // Consts();
  // Mutables();
  // ConstructorInitializerList();
  // TernaryOperators();
  // ImplicitExplicit();
  // Operators();
  // ThisKeyword();
  // ObjectLifetimes();
  // SmartPointers();
  // Copying();
  // ArrowOperator();
  // DynamicArrays();
  // DynamicArraysOptimizations();

  /* --static code example */
  // StaticFn();
  // Log("Static variable:");
  // Log(g_Variable);
  /* --static code example */

  Log("Press Enter to continue...");
  std::cin.get();
  return EXIT_SUCCESS;
}