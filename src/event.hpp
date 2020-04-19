/*
* ========================================================================= *
*        Project: Udacity - CppND - Capstone                                *
*         Author: Krzysztof Radecki ( radeckikrzysztof@gmail.com )          *
*           Date: 2020                                                      *
* ========================================================================= *
*/

/*
 * The file provides a base class for events object named EventBase.
 * Each event must inherite EventBase.
 */

#pragma once

#include <iostream>

class BaseEvent {
 public:
  
  BaseEvent() = default;

  void operator()(){ std::cout << "base class\n";} 

 private:
  unsigned score_trigger{}; // todo as shared pointer
};

class SpeedEvent : public BaseEvent
{
  public:

  SpeedEvent() = default;

  void operator()(){ std::cout << "speed class\n";} 

  private:
  int speed{};
};

class ScoreEvent : public BaseEvent
{
  public:

  ScoreEvent() = default;

  void operator()(){ std::cout << "score class\n";} 

  private:
  int score{};
};

class KeyboardEvent : public BaseEvent
{
  public:

  KeyboardEvent() = default;

  void operator()(){ std::cout << "keyboard class\n";} 
};