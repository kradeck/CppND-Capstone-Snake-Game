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

class BaseEvent 
{
 public:
  
  BaseEvent(unsigned score_trigger) : score_trigger_{score_trigger} {};
  ~BaseEvent() = default;

  /*BaseEvent(BaseEvent && rhs);
  BaseEvent & operator=(BaseEvent && rhs);*/

  virtual void operator()(){ std::cout << "base class\n";} 
  unsigned ScoreTrigger() const { return score_trigger_; }

 private:
  unsigned score_trigger_{}; // todo as shared pointer
};

class SpeedEvent : public BaseEvent
{
  public:
  SpeedEvent(const unsigned score_trigger, const float speed);
  ~SpeedEvent() = default;

  void operator()() override { std::cout << "speed class\n";} 

  private:
  float speed_{};
};

class ScoreEvent : public BaseEvent
{
  public:

  ScoreEvent(const unsigned score_trigger, const int score_bonus);
  ~ScoreEvent() = default;

  void operator()() override { std::cout << "score class\n";} 

  private:
  int score_bonus_{};
};

class KeyboardEvent : public BaseEvent
{
  public:
  KeyboardEvent(const unsigned score_trigger);
  ~KeyboardEvent() = default;

  void operator()() override { std::cout << "keyboard class\n";} 
};