#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, Snake & snake_, Score & score_)
    : snake(snake_),
      score(score_),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration,
               EventList<std::unique_ptr<BaseEvent>> && events) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();
    
    // Get the events that should appear in the current score number.
    new_events = std::move(events.get(static_cast<unsigned>(score.get())));
    if(!new_events.empty())
    {
      current_events = std::move(new_events);
    }

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, current_events);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score.get(), frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !EventsCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score.add(1);
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  CheckEvents(new_x, new_y);
  PlaceEvents();  
}

int Game::GetScore() const { return score.get(); }
int Game::GetSize() const { return snake.size; }

void Game::CheckEvents(const int x, const int y) 
{
  for(auto it = current_events.begin(); it != current_events.end();)
  {
    if((*it)->Visible())
    {
      // Check if there is event over here.
      if ((*it)->X() == x && (*it)->Y() == y)
      {
        // perform action
        (*(*it))();
        (*it)->SetVisible(false);
        // remove event
        it = current_events.erase(it);
      }
      else { ++it; }
    }  
    else { ++it; }
  }
}

void Game::PlaceEvents()
{
  // Place non visible events.
  for(auto it = current_events.begin(); it != current_events.end();)
  {
    if(!(*it)->Visible())
    {
      int x{}, y{};
      while (true) 
      {
        x = random_w(engine);
        y = random_h(engine);

        // Check that the location is not occupied by a snake,
        // food or another event before placing this event.
        if (!snake.SnakeCell(x, y) && !FoodCell(x,y) && !EventsCell(x,y)) 
        {
          (*it)->X(x);
          (*it)->Y(y);
          (*it)->SetVisible(true);
          break;
        }
      } // while          
    }
    ++it;   
  }
}

bool Game::FoodCell(const int x, const int y)
{
  if (food.x == x && food.y == y)
  {
    return true;
  }
  return false;
}

bool Game::EventsCell(const int x, const int y)
{
  for(auto it = current_events.begin(); it != current_events.end();)
  {
    if((*it)->Visible())
    {
      if((*it)->X() == x && (*it)->Y() == y)
      {
        return true;
      }
    }
    ++it;    
  }
  return false;
}