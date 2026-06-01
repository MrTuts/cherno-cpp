#include "Log.h"

void Loops()
{
  LogSectionTitle("Loops");

  for (int i = 0; i < 5; ++i)
  {
    if (i % 2 == 0)
      continue;
    // break;
    // the usual..

    Log("Inside for loop iteration");
  }
}