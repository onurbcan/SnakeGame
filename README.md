# Snake Game

I modified starter codes in the [CppND-Capstone-Snake-Game](https://github.com/udacity/CppND-Capstone-Snake-Game) GitHub repository to add some additional functionality and make changes relevant to C++ Programming, OOP (Object Oriented Programming) and Memory Management standards.

<img src="snake_game.gif"/>

Concepts that I have learned throughout [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) were integrated to this Capstone Project by extending Snake game and applying criteria addressed below.

## Changes Implemented

0. This README file is updated to inform the user about changes and playing guidance.
1. Menu screen or lines developed for a better and optimum user experience.
  * User can start, end or change settings of the game.
  * More information about the game such as instructions (in the beginning) or game statistics (at the end) is now available.
  * User submits his/her name to be be called by name and to achieve his previous top score or scores by others.
  * Difficulty level (easy, medium or hard) of the game is now choseable by the user and snake moves with the relevant speed throughout the game.
  * After each game, game duration is displayed as well as score(s) and user can start a new game or simply quit. 
2. Scores from previous plays or users are saved into GameData.txt file after each game and this file (if available) is read in the beginning of each game to compare the scores with the current game or user/users. If there is no such game data file under build folder, it is created and scores are written at the end of the game with usernames.
3. Game is also available as multiplayer. First user plays the game as usual with arrow keys and second one with A,S, D and W keys.
  * First user has a snake with blue color and commands it using right controllers (arrow keys). Second user has a snake with green color and commands it using left controllers (A, S, D and W keys).
  * Both users eat food with yellow color and make score to his/her account.
  * If a user's head crash to his/her own body or his/her opponent's body, this user loses the game and other user wins.
  * If users' heads crash each other, winner is chosen by score. If their scores are equal, there is no winner for that game.
4. Game is now more challenging with an additional food which is called Bonus Food. It is colorful by continuosly changing colors to give an idea about its limited time. After eaten or each 5 seconds, it is placed somewhere else on the grid randomly. Unlike the regular food, Bonus Food does not make snake longer but earns points same way.

## Project Criteria Addressed

* Loops, Functions, I/O
  * Criterion 1: menu.cpp
  * Criterion 2: file.cpp
  * Criterion 3: menu.cpp
* Object Oriented Programming
  * Criterion 1: menu.cpp
  * Criterion 2: menu.h, file.h, game.h, snake.h
  * Criterion 3: game.cpp
  * Criterion 4: menu.h, file.h
  * Criterion 5: menu.h, file.h, game.h
  * Criterion 6: controller.h
  * Criterion 8: controller.h
  * Criterion 9: snake.h
  * Criterion 11: game.h, game.cpp, menu.cpp
* Memory Management
  * Criterion 1: menu.cpp, file.cpp, game.cpp, snake.cpp
  * Criterion 2: menu.cpp

## Dependencies for Running Locally

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

