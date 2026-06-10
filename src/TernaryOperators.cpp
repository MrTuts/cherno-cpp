#include <string>
#include "Log.h"

static int s_Level = 1;
static int s_Speed = 2;

void TernaryOperators()
{
  LogSectionTitle("Ternary Operators");
  // basic if-else
  if (s_Level > 5)
  {
    s_Speed = 10;
  }
  else
  {
    s_Speed = 5;
  }

  // ternary operator
  s_Speed = s_Level > 5 ? 10 : 5;
  s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5; // nested ternary operator, harder to read

  std::string rank = s_Level > 10 ? "Master" : "Beginner"; // cleaner and a little bit faster

  // this way we construct string and then assign it to otherRank, this is less efficient than directly initializing otherRank with the ternary operator
  std::string otherRank;
  if (s_Level > 10)
  {
    otherRank = "Master";
  }
  else
  {
    otherRank = "Beginner";
  }
}