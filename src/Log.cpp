#include <iostream>

int Log(const char *message)
{
  std::cout << message << std::endl;
}

int Log(int value)
{
  std::cout << value << std::endl;
}

int Log(const std::string &message)
{
  std::cout << message << std::endl;
}

int LogSectionTitle(const char *message)
{
  std::cout << "====" << message << "====" << std::endl;
}