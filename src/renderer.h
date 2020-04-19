#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <list>
#include <memory>

#include "event.hpp"
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food,
              std::list<std::unique_ptr<BaseEvent>> & events);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  void RenderEvents(std::list<std::unique_ptr<BaseEvent>> & events,
                    SDL_Rect & block);
};

#endif