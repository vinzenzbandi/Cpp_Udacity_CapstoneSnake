# CPPND: Capstone Snake Game Submission

This is my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code is based on [this](https://github.com/udacity/CppND-Capstone-Snake-Game) github repository, whick was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Description
New feature was added that puts an additional food item on the field. A new food appears every 20 seconds, starts flashing after 5 seconds and disappears after 10 seconds. The additional food randomly has different properties (Normal, Superfood, Poison).

### Food Properties
* Normal (yellow): Score +1 when eaten, snake grows 1 tile
* Superfood (red): Score +2 when eaten, snake does not grow
* Poison (green): Score -1 when eaten, snake grows 1 tile

## Bug Fixes
### Snake can no longer turn back on itself
When two inputs were entered in quick succession it was possible that the snake made a 180 degree turn and died. This was fixed by ignoring inputs until the snake has moved at least one tile. 
### Food could wpawn outside the play field
There was a chance that a food spawned outside the play area because the random number generator was initialized incorrectly. 


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
4. Run it: `./SnakeGame`.