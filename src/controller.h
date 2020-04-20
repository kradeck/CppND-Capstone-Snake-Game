#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;

  bool IsReversed() const { return reversed_; }
  void Reverse(const bool reverse) { reversed_ = reverse; }

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

  // if true - the controller is reversed: kUp replaced with kDown and
  // kLeft replaced with kRight
  bool reversed_{false};
};

#endif