#include <iostream>
#include <thread>
#include "Log.h"

static bool s_Finished = false;

void DoWork()
{
  using namespace std::literals::chrono_literals; // for the 1s

  while (!s_Finished)
  {
    Log("Working...");
    // sleep for 1s
    std::this_thread::sleep_for(1s);
  }
}

void Threads()
{
  LogSectionTitle("Threads");

  // launches a new thread that calls DoWork
  std::thread worker(DoWork); // using function pointer

  std::cin.get();
  s_Finished = true;
  // wait for thread to finish
  worker.join();
  Log("Finished");
}
