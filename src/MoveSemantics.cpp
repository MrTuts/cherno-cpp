#include "Log.h"

namespace
{
  class String
  {
  public:
    String() = default;
    String(const char *string)
    {
      Log("Created");
      m_Size = strlen(string);
      m_Data = new char[m_Size];
      memcpy(m_Data, string, m_Size);
    }
    ~String()
    {
      Log("Destroyed");
      delete[] m_Data;
    }

    String(const String &other)
    {
      Log("Copied");
      m_Size = other.m_Size;
      m_Data = new char[m_Size];
      memcpy(m_Data, other.m_Data, m_Size);
    }

    // Move constructor - takes rvalue reference (see LRValues)
    // noexcept - should not throw exceptions
    String(String &&other) noexcept
    {
      Log("Moved");
      // shallow copy
      m_Size = other.m_Size;
      m_Data = other.m_Data; // point to the same data

      // Hollow object
      // We need to "deinitialize" the old "other" String, so when it is destructed
      // it does not destroy data new String is pointing to
      other.m_Size = 0;
      other.m_Data = nullptr;
    }

    void Print()
    {
      for (u_int32_t i = 0; i < m_Size; i++)
      {
        printf("%c", m_Data[i]);
      }
      printf("\n");
    }

  private:
    char *m_Data;
    uint32_t m_Size;
  };

  class Entity
  {
  public:
    Entity(const String &name) : m_Name(name) {}
    // work with the move constructor of String.
    // We need to also cast the name to (String &&)
    // Or use std::move (the common approach), which essentially does the same thing
    // Entity(String &&name) : m_Name((String &&)name) {}
    Entity(String &&name) : m_Name(std::move(name)) {}

    /*
    This version crashes app, it does a shallow copy of name into m_Name, which is already initialized.
    This means data point to the same memory address, which is later deleted, because `name` is temporary value
    destructed after constructor ends
    In our move constructor we are also doing shallow copy, but we are also transforming the temporary object to hollow object
    */
    // Entity(const String &name)
    // {
    //
    //   m_Name = name;
    // }

    void PrintName()
    {
      m_Name.Print();
    }

  private:
    String m_Name;
  };
}

void MoveSemantics()
{
  LogSectionTitle("Move Semantics");

  // Explicitly creates a temporary String from "Pavel".
  // The temporary is an rvalue, so Entity(String&&) is selected.
  // Inside Entity(String&&), std::move(name) allows m_Name to be move-constructed.
  Entity entity(String("Pavel"));
  entity.PrintName();
  Log("---");

  // "George" is a const char*, which can be converted to a temporary String.
  // That temporary String is an rvalue, so Entity(String&&) is selected.
  // m_Name is then move-constructed from that temporary.
  Entity entity2("George");
  entity2.PrintName();
  Log("---");

  String str("Karel");
  // str is a named variable, so it is an lvalue.
  // Entity(const String&) is selected, and m_Name is copy-constructed.
  Entity entity3(str);
  Log("---");
}