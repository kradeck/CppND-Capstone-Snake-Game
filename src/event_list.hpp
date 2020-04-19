/*
* ========================================================================= *
*        Project: Udacity - CppND - Capstone                                *
*         Author: Krzysztof Radecki ( radeckikrzysztof@gmail.com )          *
*           Date: 2020                                                      *
* ========================================================================= *
*/

/*
 * The file provides a template list container to store events.
 * The container is the list because we don't want to store
 * events in a specific order. We may want to take an event from 
 * the middle of the list or even we may want to tak more than one
 * event from a list. 
 */

#pragma once

#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>

template <typename T>
class EventList {
 public:
  
  EventList() = default;

  EventList(EventList && rhs) :
    list_{std::move(rhs.list_)}
  {}

  EventList & operator=(EventList && rhs)
  {
    if(&rhs != this)
    {
      list_ = std::move(rhs.list_);
    }
    return *this;
  }

  void add(T && event);
  // we return the list of events that meet required criteria
  std::list<T> get(const unsigned score_trigger);

  // useful in debug
  auto begin() const { return list_.begin(); }
  auto end() const { return list_.end(); }

 private:
  std::list<T> list_{};
  std::mutex mutex_{};
};

template <typename T>
void EventList<T>::add(T && event)
{
  std::lock_guard<std::mutex> guard(mutex_);
  list_.push_back(std::move(event));
}

template <typename T>
std::list<T> EventList<T>::get(const unsigned score_trigger)
{
  std::unique_lock<std::mutex> guard(mutex_);

  std::list<T> events{};

  std::remove_if(list_.begin(), list_.end(), [&](auto & e)
  {
    if(e.trigger() == score_trigger)
    {
      events.push_back(std::move(e));
      return true;
    }
    return false;
  });

  return events;
}
