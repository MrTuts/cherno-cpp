#include "Log.h"
#include <string>
#include <vector>
#include <unordered_map>

std::string GetName()
{
  return "Name";
}

namespace
{
  class Device
  {
  };

  class DeviceManager
  {
  private:
    std::unordered_map<std::string, std::vector<Device *>> m_Devices;

  public:
    const std::unordered_map<std::string, std::vector<Device *>> &GetDevices() const
    {
      return m_Devices;
    }
  };
}

void AutoKeyword()
{
  LogSectionTitle("Auto keyword");

  int a = 5;
  auto b = a; // automatically deduces the type of b to be int
  auto c = 5; // automatically deduces the type of c to be int
  auto cf = 5.4f;
  // but do not use auto for simple variables

  auto name = GetName();
  // it's better to NOT use auto here, so we can see the type of variable immediately.
  std::string name2 = GetName();

  std::vector<std::string> strings;
  strings.push_back("Apple");
  strings.push_back("Orange");

  for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); it++)
  {
    Log(*it);
  }

  // here auto is usefull because we can avoid specifying lengthy type and the type of "it" is
  // simply deductible from the code itself
  for (auto it = strings.begin(); it != strings.end(); it++)
  {
    Log(*it);
  }

  // create type alias for a lengthy type name
  // this would be good to have included in DeviceManager class, so we can use it by including the DeviceManaget
  using DeviceMap = std::unordered_map<std::string, std::vector<Device *>>;
  // the same as with "using"?
  // typedef std::unordered_map<std::string, std::vector<Device *>> DeviceMap;

  DeviceManager dm;
  const DeviceMap devices = dm.GetDevices();
  // or use auto
  const auto &devices2 = dm.GetDevices(); // we need to also include &
  // !!No &, this would make a copy of devices!!
  // const auto devices2 = dm.GetDevices();
}