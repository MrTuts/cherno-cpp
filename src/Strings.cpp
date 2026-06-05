#include "Log.h"
#include <iostream>
// even though <iostream> has definition for std::string, we need <string> because it has overload for
// std::cout << std::string, without it we would get an error because it would not know how to print std::string
#include <string>

// this would have copy the string
// void PrintString(std::string str){
// str is passed as reference -> we cannot modify the original string, but we can read it
void PrintString(const std::string &str)
{
  std::cout << str << std::endl;
}

void StringLiterals()
{
  LogSectionTitle("String Literals");
  // this is a string literal
  const char *name = "Pavel"; // (const char [6])"Pavel" - it includes the null terminator, so it is 6 bytes long, the last byte is '\0'
  // This could mess up the string, because it has a null terminator in the middle, so it would be treated as "Pa" and the rest would be ignored
  const char *name2 = "Pa\0vel";
  const char *multiline = R"(Line1
    Line2
    Line3)"; // The "R" in front allows us to create raw (The R stands for raw) string literal, it allows us to include special characters without escaping
  const char *multiline2 = "Line1\n"
                           "Line2\n"
                           "Line3"; // This is also a valid way to create a multiline string literal

  Log(multiline);
  Log(multiline2);
  Log(name);
  Log(name2);         // prints out "Pa"
  Log(strlen(name2)); // prints out 2

  const char *name_ = u8"Pavel";    // 1 byte per character
                                    /*
                                    difference between wchar_t and char16_t is that wchar_t can be 2 bytes or 4 bytes depending on the platform,
                                    while char16_t is always 2 bytes, so it is more portable for UTF-16 strings
                                    */
  const wchar_t *name3 = L"Pavel";  // wide string literal, it is stored as an array of wchar_t, which is usually 2 bytes per character (but it can be 4 bytes on some platforms)
  const char16_t *name4 = u"Pavel"; // UTF-16 string literal, it is stored as an array of char16_t, which is 2 bytes per character
  const char32_t *name5 = U"Pavel"; // UTF-32 string literal, it is stored as an array of char32_t, which is 4 bytes per character

  std::string combined = std::string("Hello") + " World";
  using namespace std::string_literals; // this allows us to use the "s" suffix to create a std::string from a string literal
  std::string combined2 = "Hello"s + " World";
  std::wstring combined3 = L"Hello"s + L" World";
  std::u16string combined4 = u"Hello"s + u" World";
  std::u32string combined5 = U"Hello"s + U" World";
}

void Strings()
{
  LogSectionTitle("Strings");

  // strings are immutable, fix allocated block of memory, so we cannot modify the string literal,
  // therefore we use const char* to prevent modification of the string literal (it won't compile if we try to modify it)
  char *_name = "Pavel";      // is possible, but it is not recommended
  const char *name = "Pavel"; // string literal, stored in read-only memory (it is part of compiled binary), cannot be modified
  // _name[2] = 'x'; this compiles, but throws at runtime (EXC_BAD_ACCESS). C++ standart does not define what should happen
  // "Pavel" would be stored as bytes ['P', 'a', 'v', 'e', 'l', '\0'] in memory, the last byte is the null terminator,
  // which indicates the end of the string

  // this is an array of characters, it is mutable, it has a null terminator at the end, so it is a valid C-style string
  // The string literal "Pavel" is still stored in read-only memory, but when we initialize the array nameArr with it,
  // it copies the characters into the array, so we have a mutable copy of the string literal that we can modify without
  // affecting the original string literal in read-only memory.
  char nameArr[] = "Pavel";
  nameArr[2] = 'x'; // this is allowed, because nameArr is an array of characters
  Log(nameArr);

  // double quotes are used for string literals, by default they become char pointer
  // single quotes are used for character literals
  // this is not a string literal, it is an array of characters, it does not have a null terminator, so it is not a valid C-style string
  char name2[5] = {'P', 'a', 'v', 'e', 'l'};
  char name3[6] = {'P', 'a', 'v', 'e', 'l', '\0' /* or simply 0 */};
  Log(std::string("name: ") + name);
  Log(strlen(name)); // get size of the string, does not include the null terminator
  // this might not print "Pavel", because it does not have a null terminator,
  // it might print "Pavel" followed by some garbage characters until it finds a null terminator in memory.
  // Probably depending on the compiler and optimization settings
  Log(std::string("name2: ") + name2);
  // this will print "Pavel", because it has a null terminator, so it knows where the string ends
  Log(std::string("name3: ") + name3);

  std::string name4 = "Pavel"; // std::string is a class that represents a string, it is mutable, it can be modified
  Log("name4: " + name4);
  name4[2] = 'x'; // we can modify the string, because it is mutable
  Log("name4: " + name4);
  Log(name4.size()); // get size of the string, does not include the null terminator, std::string does not have a null terminator, it manages its own memory

  /* Appending strings */

  // This does not work, because "Pavel" is a const char* and ", Hi!" is also a const char*, we cannot add two pointers together
  // std::string name5 = "Pavel" + ", Hi!";
  std::string name5 = "Pavel";
  name5 += ", Hi!"; // this works, because std::string has an overloaded operator+= that allows us to append strings
  Log("name5: " + name5);

  // this works, because we are creating a temporary std::string from the const char* "Pavel",
  // and then we can use the overloaded operator+ to append ", Hi!"
  std::string name6 = std::string("Pavel") + ", Hi!";
  Log("name6: " + name6);

  // find returns the index of the first occurrence of the substring, or std::string::npos if it is not found
  size_t index = name6.find("ve");
  std::cout << "index of 've' in name6: " << index << std::endl; // prints 2, because 'v' is at index 2 and 'e' is at index 3
  bool contains = name6.find("ve") != std::string::npos;
  std::cout << "name6 contains 've': " << contains << std::endl; // prints 1 (true), because name6 does contain "ve"

  StringLiterals();
}
