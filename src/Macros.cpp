#include <iostream>
#include "Log.h"

// during preprocessor stage the WAIT anywhere in our code is just replaced with the std::cin.get()
// this is not a good example for usage of macros
#define WAIT std::cin.get()

// we can also define multiple line macros by escaping enter press with backlash
#define PRINT                    \
  void print(std::string x)      \
  {                              \
    std::cout << x << std::endl; \
  }

// using preprocessor definition to modify definitions depending on build env
#ifdef DEBUG // DEBUG is a preprocessor definition defined in tasks.json
// Macro with parameter to log to console
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

// another way to write if statement, here the preprocessor definition has assigned value
#if PR_DEBUG == 1 // PR_DEBUG is a preprocessor definition defined in tasks.json
// Macro with parameter to log to console
#define LOG2(x) std::cout << x << std::endl
#else
#define LOG2(x)
#endif

#if 0 // disabling code using macro
#define LOG3(x)
#endif

// use the definition to include the print function
PRINT;

void Macros()
{
  LogSectionTitle("Macros");

  LOG("LOG Hello");
  LOG2("LOG2 Hello");
  print("print Hello");
  WAIT;
}