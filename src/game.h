#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <random>
#include <chrono>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game() {}
  Game(int grid_width, int grid_height, int difficultyLevelR);
  Game(int grid_width, int grid_height, int difficultyLevelR, int difficultyLevelL);
  void RunSingle(std::shared_ptr<Controller> const &controllerR, 
           Renderer &renderer, std::size_t target_frame_duration, double &gameDuration);
  void RunMulti(std::shared_ptr<Controller> const &controllerR, 
           std::shared_ptr<Controller> const &controllerL, Renderer &renderer,
           std::size_t target_frame_duration, double &gameDuration); 
  int GetScoreR() const { return scoreR; }
  int GetScoreL() const { return scoreL; }
  int GetSizeR() const { return snakeR->size; }
  int GetSizeL() const { return snakeL->size; }
  int GetWinner() const;
 
 private:
  std::shared_ptr<Snake> snakeR; // Right snake (blue colored), first and main user, commanded by right controller
  std::shared_ptr<Snake> snakeL; // Left snake (green colored), second user which is created for the multiplayer aim,
                                    // commanded by left controller

  SDL_Point food; // Main food, yellow color and makes the snake longer when it is eaten
  SDL_Point bonusFood; // Bonus food, colorful by changing continuously to give the idea of limited time
                          // of 5 seconds, after each and every 5 seconds bonus food is placed somewhere else,
                          // by eating bonus food user makes score without making its snake longer

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::chrono::time_point<std::chrono::system_clock> startTime, endTime; // Time variables for the length of the game
  std::chrono::time_point<std::chrono::system_clock> beginTime = std::chrono::system_clock::now(), scoreTime; // Time
                  // variables for the time length detection of bonus food, 5 seconds rule 
  
  int difficultyLevelR{0};
  int difficultyLevelL{0};
  int scoreR{0}; // Score for the right snake
  int scoreL{0}; // Score for the left snake
  double bonusFoodDuration; // Calculated time for the bonus food after conversion to double type

  void PlaceFoodSingle(); 
  void PlaceBonusFoodSingle();
  void PlaceFoodMulti(); 
  void PlaceBonusFoodMulti();
  void UpdateSingle(bool &running, double &gameDuration);
  void UpdateMulti(bool &running, double &gameDuration);
};

#endif