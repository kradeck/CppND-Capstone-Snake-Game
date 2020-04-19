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
#include "snake.h"
#include "controller.h"

struct Color
{
  uint8_t r{255};
  uint8_t g{255};
  uint8_t b{255};
  uint8_t a{255};
};

class BaseEvent 
{
 public:
  
  BaseEvent(unsigned score_trigger, Color color = {255,255,255,255}) : 
    score_trigger_{score_trigger},
    color_{color} {};
  ~BaseEvent() = default;

  virtual void operator()(){ std::cout << "base class\n";} 
  unsigned ScoreTrigger() const { return score_trigger_; }
  bool Visible() const { return visible_; }
  void SetVisible(const bool & visible) { visible_ = visible; }
  int X() const { return position_.x; };
  void X(int x) { position_.x = x; }
  int Y() const { return position_.y; };
  void Y(int y) { position_.y = y; }

  uint8_t R() const { return color_.r; }
  uint8_t G() const { return color_.g; }
  uint8_t B() const { return color_.b; }
  uint8_t A() const { return color_.a; }

 private:
  unsigned score_trigger_{};
  bool visible_{false};
  SDL_Point position_{};
  Color color_{};
};

class SpeedEvent : public BaseEvent
{
  public:
  SpeedEvent(const unsigned score_trigger, const float speed, Snake & snake);
  ~SpeedEvent() = default;

  void operator()() override;

  private:
  float speed_{};
  Snake & snake_;
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
  KeyboardEvent(const unsigned score_trigger, Controller & controller);
  ~KeyboardEvent() = default;

  void operator()() override; 

  private:
  Controller & controller_;
};