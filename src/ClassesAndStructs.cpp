#include <iostream>
#include "Log.h"

/*
  Class is private by default, struct is public by default
  C does not have classes, only structs, so structs are kept for compatibility reasons

  use struct for plain data structures, may have methods to operate on the data, but should not have complex behavior. Do not use for inheritance or polymorphism.
  Use class for everything else, especially if you need encapsulation, inheritance, or polymorphism.

  This would make struct behave like class, but it's not recommended, because it can be confusing
  #define struct class
*/
namespace
{

  class Player
  {
    int health; // private by default

  public:
    int x, y;
    int speed;

    /* Constructors */
    Player()
    {
      Log("Player constructor called");
      // We need to manually initialize the members, otherwise they will have uninitialized values (garbage values)
      health = 100;
      x = 0;
      y = 0;
      speed = 5;
    }

    Player(int X, int y)
    {
      Log("Player constructor with parameters called");
      x = X;
      this->y = y; // this is a pointer to the current instance of the class, we need to use it to distinguish between the parameter y and the member variable y
      speed = 5;
      health = 100;
    }

    /* Destructor */
    ~Player()
    {
      Log("Player destructor called");
    }

    /* Methods */
    void Move(int xDir, int yDir)
    {
      x += xDir * speed;
      y += yDir * speed;
    }

    void Print()
    {
      std::cout << "X: " << x << ", Y: " << y << ", Health: " << health << std::endl;
    }
  };

  struct PlayerStruct
  {
    int x, y; // public by default
    int speed;

    void Move(int xDir, int yDir)
    {
      x += xDir * speed;
      y += yDir * speed;
    }

  private:
    int health;
  };

  class LogClass
  {
  public:
    enum Level
    {
      // (Error, Warning, Info) would create name conflicts with the log level functions, so we prefix them with Level to avoid that.
      LevelError = 0,
      LevelWarning = 1,
      LevelInfo = 2
    };

  private:
    Level m_LogLevel = LevelInfo; // prefix m_ for private class members

  public:
    void SetLevel(Level level)
    {
      m_LogLevel = level;
    }

    void Error(const char *message)
    {
      if (m_LogLevel >= LevelError)
      {
        std::cout << "[ERROR]: " << message << std::endl;
      }
    }

    void Warn(const char *message)
    {
      if (m_LogLevel >= LevelWarning)
      {
        std::cout << "[WARNING]: " << message << std::endl;
      }
    }

    void Info(const char *message)
    {
      if (m_LogLevel >= LevelInfo)
      {
        std::cout << "[INFO]: " << message << std::endl;
      }
    }
  };

  /* START Disable creating instances */

  // approach 1
  class OnlyStaticLog
  {
  private:
    OnlyStaticLog() {} // private constructor to prevent instantiation of the class

  public:
    static void StaticLog(const char *message)
    {
      std::cout << "[STATIC LOG]: " << message << std::endl;
    }
  };

  // approach 2
  class OnlyStaticLog2
  {
  public:
    OnlyStaticLog2() = delete; // delete the constructor to prevent instantiation of the class

    static void StaticLog(const char *message)
    {
      std::cout << "[STATIC LOG]: " << message << std::endl;
    }
  };
  /* END Disable creating instances */
}

void ClassesAndStructs()
{
  LogSectionTitle("Classes and Structs");
  /* These instances are created on the stack, which means they are automatically destroyed when they go out of scope (when the function ends). */

  Player player;
  player.x = 0;
  player.y = 0;
  player.speed = 5;
  player.Move(1, -1); // move right
  // player.health -= 5; NO, is private

  player.~Player(); // call destructor manually, but it's not recommended

  Player player1;
  // uninitialized values, will print anything currently at the memory location of player0
  // that would be true, if Player did not have a constructor, since we added it, the values are initialized
  player1.Print();

  Player player2(2, 3); // constructor with parameters
  player2.Print();

  PlayerStruct playerStruct;

  playerStruct.x = 0;
  playerStruct.y = 0;
  playerStruct.speed = 5;
  playerStruct.Move(1, -1); // move right
  // playerStruct.health -= 5; NO, is private

  LogClass log;
  log.SetLevel(LogClass::LevelWarning);
  log.Warn("This is a warning");
  log.Info("This is an info message");
  log.Error("This is an error message");

  OnlyStaticLog::StaticLog("This is a static log message");
  // OnlyStaticLog staticLog; // we cannot create an instance of the class, because the constructor is private

  OnlyStaticLog2::StaticLog("This is a static log message");
  // OnlyStaticLog2 staticLog; // we cannot create an instance of the class, because the constructor is deleted
}