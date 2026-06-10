#include "Log.h"

namespace
{
  class Entity
  {
  private:
    mutable int m_var; // allows us to modify variable in const functions
    int m_X, m_Y;
    int *mp_X, *mp_Y; // we must add * to each pointer variable for it to be a pointer, otherwise it would be just an int variable

  public:
    Entity()
    {
      m_X = 0;
      m_Y = 0;
      mp_X = new int; // we must allocate memory for the pointer variables, otherwise they would be uninitialized and could cause a crash when we try to dereference them
      mp_Y = new int;
      *mp_X = 0; // we must also initialize the values that the pointer variables point to, otherwise they would be uninitialized and could cause a crash when we try to dereference them
      *mp_Y = 0;
    }
    ~Entity()
    {
      delete mp_X;
      delete mp_Y;
    }

    // const here disallows us from changing the class values. This can be used in classes only
    int GetX() const
    {
      // m_X = 5; // this causes a compile error, because we cannot change the value of m_X in a const function
      m_var = 5; // this is allowed, because m_var is mutable, which means we can change its value even in a const function
      return m_X;
    }

    // 1st const: we are returning a pointer, that cannot be modified
    // 2nd const: we cannot change the value of mp_X
    // 3rd const: we cannot change the value of mp_X in this function, because it is a const function
    const int *const GetPX() const
    {
      *mp_X = 20; // this is stills allowed!!
      // mp_X = new int; // this is not allowed, because we are changing the value of mp_X, which is not allowed in a const function
      return mp_X;
    }

    void SetX(int x)
    {
      m_X = x;
    }
  };
}

static void PrintEntity(Entity &e)
{
  e.SetX(5); // IS ALLOWED
  Log(e.GetPX());
}

// Disable modifying the entity
static void PrintEntity(const Entity &e)
{
  // e.SetPX(5) NOT ALLOWED
  // e = new Entity(); NOT ALLOWED, because e is a reference to a const Entity, so we cannot change where it points to
  Log(e.GetX());
  Log(e.GetPX());
}
static void PrintEntity(Entity *e)
{
  e = new Entity(); // IS ALLOWED, we can change where e points to
  e->SetX(5);       // IS ALLOWED, because we are changing the value of the entity that e points to, not where e points to
  Log(e->GetX());
  Log(e->GetPX());
}
static void PrintEntity(const Entity *e)
{
  e = new Entity(); // IS ALLOWED, we can change where e points to
  // e->SetX(5); // NOT ALLOWED
  Log(e->GetX());
  Log(e->GetPX());
}
// this would collide with `static void PrintEntity(const Entity *e)` implementation,
// because the only difference is the const qualifier, which is not enough for the compiler to distinguish between the two functions.
// This would cause a compile error due to function overloading ambiguity.
static void PrintEntity2(const Entity *const e)
{
  // e = new Entity(); // NOT ALLOWED, we cannot change where e points to
  // e->SetX(5); // NOT ALLOWED, we cannot change the value of the entity
  Log(e->GetX());
  Log(e->GetPX());
}

void Consts()
{
  const int MAX_AGE = 62;

  const int a = 5;
  // this would cause a compile error, because a is const and cannot be changed after initialization
  // a = 2;

  int *b = new int;
  *b = 2;
  // change the value of b to point to MAX_AGE
  // We must cast MAX_AGE to int* because it is a const int, and we want to treat it as a pointer to int.
  // This is not safe, but it is possible in C++. We are essentially telling the compiler to ignore the const qualifier
  // and treat MAX_AGE as a regular int.
  // This might lead to crash
  b = (int *)&MAX_AGE;
  Log(*b); // prints 62, because b now points to MAX_AGE
  // this now cause a crash, because we are trying to delete a pointer that points to a const int, which is not allowed.
  // We are trying to delete memory that was not allocated with new.
  // delete b;

  const int *c = new int;
  // int const *c = new int; // could be also be written like this
  // *c = 3; // we cannot change the value of c, because it is a pointer to a const int
  c = (int *)&MAX_AGE; // this can be done, because we are changing where c points to, not the value of the const int that c points to
  Log(*c);

  int *const d = new int;
  // int const *d = new int; // BEWARE: this is the same as int *const d = new int; because the const qualifier applies to the pointer, not the value it points to
  *d = 3; // we can change the value of d
  // d = (int *)&MAX_AGE; // we cannot change where d points to, because it is a const pointer, so this would cause a compile error
  Log(*d);

  const int *const e = new int;
  // *e = 3; // we cannot change the value of d
  // e = (int *)&MAX_AGE; // we cannot change where d points to
  Log(*e);

  Entity entity;
  entity.SetX(5);
  Log(entity.GetX());  // prints 5
  Log(entity.GetPX()); // prints 5
}