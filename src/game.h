#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <mutex>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "event_list.hpp"
#include "event.hpp"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration,
           EventList<std::unique_ptr<BaseEvent>> && events);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::mutex mutex;

  // to store events in the current game loop iteration
  std::list<std::unique_ptr<BaseEvent>> current_events{};
  // to store events from the previous game loop iteration
  std::list<std::unique_ptr<BaseEvent>> new_events{};

  int score{0};

  void PlaceFood();
  void Update();

  void CheckEvents(const int x, const int y);
  void PlaceEvents();
  bool FoodCell(const int x, const int y);
  bool EventsCell(const int x, const int y);
};

#endif