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

## Addressed Rubric Points
### The project demonstrates an understanding of C++ functions and control structures.
Throughout the project functions are used to make the code readable and organized. For example a Renderer::RenderFood (renderer.cpp 84) function was separated form the Renderer::Render function to make it more readable.

### The project uses Object Oriented Programming techniques.
The food objects are organized in a new class (food.h/food.cpp)

### Classes use appropriate access specifiers for class members.
All data members of the food class are private and can only be accessed through setters and getters.

### Class constructors utilize member initialization lists.
For the food class there is a constructor that has the foodtype as an argument, it uses an initialization list to set the type (food.cpp 16).

### Classes abstract implementation details from their interfaces.
Functions have obvious names such as setActive(bool state) or a short comment explaining the function.

### Classes encapsulate behavior.
A new food class was introduced (as mentioned above)

### The project makes use of references in function declarations.
All instances of food are passed by reference (e.g. renderer.h 15/19)

### The project follows the Rule of 5.
The rule of 5 was applied to the Food class (food.h/food.cpp) in order to handle the mutex correctly, since mutexes cannot be moved or copied.

### The project uses multithreading.
The Food class uses detached threads to update properties of the "random" foods (food.cpp 143/178)

### A mutex or lock is used in the project.
In the Food class a mutex is added to protect all members that are changed within the timing threads. These members are only accessed through setters and getters and the locks are acquired within the setters and getters.
