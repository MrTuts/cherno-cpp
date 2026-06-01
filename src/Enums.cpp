enum Example
{
  A,
  B,
  C
};

enum Example2 : unsigned int
{
  A2 = 2,
  B2 = 4,
  C2 = 8
};

enum Example3 : unsigned char
{
  A3 = 2,
  B3,
  C3
};

void Enums()
{
  Example value = B;

  if (value == B    // valid, comparing enum value to its enumerator
      || value == 1 // also valid since B is implicitly converted to its underlying integer value (1 in this case, since A is 0, B is 1, C is 2)
  )
  {
    // Do something
  }

  if (value == 1)
  {
    // Do something
  }
}