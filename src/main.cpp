#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "config_file_parser.hpp"

// I don't want the ConfigFileParser object alive for the whole program
// so with the variables scope rules tha usage is in a separate function
// (also for better refactorization).
void load_config(const std::string & fileName)
{
  try{
    ConfigFileParser fp(fileName);
    auto params = fp();

    // debug
    /*for(auto & e : params)
    {
      std::cout << e.first <<" " << e.second << "\n";
    }*/

  } catch(std::ios_base::failure & e) {
    std::cout << e.what() << "\n";
  } catch (...) {
    std::cout << "Cannot load event config file: unknown error :(\n";
  }
}

int main(int argc, char *argv[]) {

  // default path if the event config file is 
  // in the same directory 
  // with the executable file
  std::string config_event_file{"example_config.cfg"};

  // check if the file name is provided from the command line
  if(argc == 2)
  {
    config_event_file = argv[1];
  }

  load_config(config_event_file);

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}