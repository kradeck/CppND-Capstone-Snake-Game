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
#include "SDL.h"

class BaseEvent 
{
 public:
  
  BaseEvent(unsigned score_trigger) : score_trigger_{score_trigger} {};
  ~BaseEvent() = default;

  virtual void operator()(){ std::cout << "base class\n";} 
  unsigned ScoreTrigger() const { return score_trigger_; }
  bool Visible() const { return visible_; }
  void SetVisible(const bool & visible) { visible_ = visible; }
  int X() const { return position_.x; };
  void X(int x) { position_.x = x; }
  int Y() const { return position_.y; };
  void Y(int y) { position_.y = y; }

 private:
  unsigned score_trigger_{};
  bool visible_{false};
  SDL_Point position_{};
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