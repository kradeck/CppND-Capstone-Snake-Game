# CPPND: Capstone Snake Game 

This is a Snake Game extended with special events for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 
The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The events are special fields that the snake can eat and change the behaviour of the game. The events will appear when you get required number of the score. They will disappear when the snake will eat them or the new event will appear. In one time there can even be more than one event on the map.

Events that may occur:
```
green   - the speed of the snake is changed
red     - get extra 10 score
purple  - keyboard control is reversed
```
<img src="snake_screen.png"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Copy `example_config.cfg` from the `resources` directory to the `build` directory withe the game executable file.
5. Run it: `./SnakeGame`.

### Additionally

You can build your own scenario with the events. Write your own configuration file and run your game with the instruction `./SnakeGame path_to_event_scenario_file`.

In the scenario file write the name of the event and the number of the score when the event should appear.

Example:
```
speed_up 1
speed_down 3
extra_score 3
reverse_keyboard 1
reverse_keyboard 2
```

Possible events:
speed_up          - add extra speed to the snake 
speed_down        - the snake is slower
extra_score       - get extra 10 score
reverse_keyboard  - change the keyboard control (up key replace with down key, and left key replace with right key)

## For the reviewer

### main.cpp

```
In line 134-145 there is checked command line argument with the config file name.

150: The score is en external object - not a variable inside the game class.
151: Snake is created in main function - not inside the game class.

152: The config file is loaded ->
    120: get_events function ->
        125: the config file content is loaded first, then the list of parameters is passed to the
        126: create_events function. The events are created and added to the events list.
    The event list is returned.
163: The game constructor is called with reference to snake and score objects.
164: The run method is called with moved events list.
```



