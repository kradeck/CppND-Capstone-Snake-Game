#include <iostream>
#include <memory>

#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "config_file_parser.hpp"
#include "event_list.hpp"
#include "event.hpp"

template<typename T>
void display_exception(T & exception)
{
  std::cout << "Please check if the event config file is correct: "
            << exception.what() << "\n";
}

// I don't want the ConfigFileParser object alive for the whole program
// so with the variables scope rules tha usage is in a separate function
// (also for better refactorization).
std::vector<std::pair<std::string, std::string>> load_config(const std::string & fileName)
{
  try{
    ConfigFileParser fp(fileName);
    auto params = fp();

    // debug
    /*for(auto & e : params)
    {
      std::cout << e.first <<" " << e.second << "\n";
    }*/

    return params;
  } catch(std::ios_base::failure & e) {
    display_exception(e);
    // empty vector is returned - the game should run without events
    return std::vector<std::pair<std::string, std::string>>{};
  } catch (...) {
    std::cout << "Cannot load event config file: unknown error :(\n";
    // empty vector is returned - the game should run without events
    return std::vector<std::pair<std::string, std::string>>{};
  }
}

EventList<std::unique_ptr<BaseEvent>> create_events(std::vector<std::pair<std::string, std::string>> && params)
{
  const float speed_up{0.04f};
  const float speed_down{-0.04f};
  // bonus can also be negative so int is used instead of unsigned,
  // but in this version only positive bonus usage is provided
  const int score_bonus{10}; 
  
  using ptr_e = std::unique_ptr<BaseEvent>;

  EventList<ptr_e> list;
  // if the wrong value is provided - exception is thrown,
  // no reason to parse and load events further
  try {
    for(auto & event : params)
    {
      // casting unsigned long to unsigned - no matter if uunsigned long
      // is reduced to unsigned range
      auto score_trigger{static_cast<unsigned>(std::stoul(event.second))};

      if(event.first == "speed_up")
      {
        ptr_e event = std::make_unique<SpeedEvent>(score_trigger, speed_up);
        list.add(std::move(event));
      }
      else if(event.first == "speed_down")
      {
        ptr_e event = std::make_unique<SpeedEvent>(score_trigger, speed_down);
        list.add(std::move(event));
      }
      else if(event.first == "extra_score")
      {
        ptr_e event = std::make_unique<ScoreEvent>(score_trigger, score_bonus);
        list.add(std::move(event));
      }
      else if(event.first == "reverse_keyboard")
      {
        ptr_e event = std::make_unique<KeyboardEvent>(score_trigger);
        list.add(std::move(event));
      }
      else 
      {
        throw(std::runtime_error("unknown event name"));
      }    
    } // for(auto & event : params)
    return list;

  } catch (std:: invalid_argument & e) {
      display_exception(e);

      // empty list is returned - the game should run without events
      return EventList<ptr_e>{};
    } catch (std::out_of_range & e) {
      display_exception(e);

      // empty list is returned - the game should run without events
      return EventList<ptr_e>{};
    } catch (std::runtime_error & e) {
      display_exception(e);

      // empty list is returned - the game should run without events 
      return EventList<ptr_e>{};
    } catch (...) {
      std::cout << "Please check if the event config file is correct: "
                << "unknown error\n";
      // empty list is returned - the game should run without events
      return EventList<ptr_e>{};
    }
}

void get_events(std::string & fileName)
{
  auto params = load_config(fileName);
  auto list = std::move(create_events(std::move(params)));  

  for(auto & l : list)
  {
    (*l)();
    std::cout << l->ScoreTrigger() << "\n";
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

  /*auto events = */get_events(config_event_file);

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