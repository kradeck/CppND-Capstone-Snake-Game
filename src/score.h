/*
* ========================================================================= *
*        Project: Udacity - CppND - Capstone                                *
*         Author: Krzysztof Radecki ( radeckikrzysztof@gmail.com )          *
*           Date: 2020                                                      *
* ========================================================================= *
*/

/*
 * The class provides a simply interface to keep the score.
 */

#pragma once

class Score 
{
 public:
  void add(const int value) { score_ += value; }
  auto get() const { return score_; }

 private:
  int score_{};
};

