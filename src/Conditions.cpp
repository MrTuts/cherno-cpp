#include "Log.h"

void Conditions()
{
  Log("====Conditions====");
  int x = 5;

  bool comparison = x == 5;
  Log("  if (comparison)");
  if (comparison)
  {
    Log("x is equal to 5");
  }
  else
  {
    Log("x is not equal to 5");
  }

  Log("  if (x == 5)");
  if (x == 5)
    Log("x is equal to 5");

  Log("  if (x)");
  if (x)
    Log("x is equal to 5");

  Log("  if (ptr)");
  const char *ptr = "Hello";
  if (ptr)
    Log(ptr);

  Log("  if (ptrNull)");
  const char *ptrNull = nullptr;
  if (ptrNull)
    Log("Won't be printed");
  else
    Log("ptrNull is null (else block)");

  Log("  if (!ptrNull)");
  if (!ptrNull)
    Log("ptrNull is null");
}