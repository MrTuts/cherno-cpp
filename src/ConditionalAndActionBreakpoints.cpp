#include "Log.h"
#include <iostream>
#include <string>
#include <thread>

static bool s_Finished = false;

static void DoWork()
{
  using namespace std::literals::chrono_literals; // for the 1s

  int a = 0;

  while (!s_Finished)
  {
    a++;
    /* Add and play with breakpoints here */
    std::this_thread::sleep_for(0.1s);
  }
}

// https://www.youtube.com/watch?v=9ncNA6Co2Nk&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=70
void ConditionalAndActionBreakpoints()
{
  LogSectionTitle("ConditionalAndActionBreakpoints");
  /*
    This was about adding conditions to breakpoints, log message instead of pausing the program etc. and is
    dependent on the IDE being used.
  */

  Log("Start worker");
  std::thread worker(DoWork); // using function pointer

  std::cin.get();
  Log("End worker");
  s_Finished = true;
  worker.join();
}