#ifndef GAME_H
#define GAME_H

#include <random>
#include <chrono>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(int grid_width, int grid_height);
  void Run(std::shared_ptr<Controller> const &controllerR, 
           std::shared_ptr<Controller> const &controllerL, Renderer &renderer,
           std::size_t target_frame_duration, int diffLevel, double &gameDuration);
  int GetScoreR() const;
  int GetScoreL() const;
  int GetSizeR() const;
  int GetSizeL() const;
  int GetWinner() const;

 //private:
  std::shared_ptr<Snake> snakeR;// = std::make_shared<Snake>(std::size_t, std::size_t);
  std::shared_ptr<Snake> snakeL;

  SDL_Point food;
  SDL_Point bonusFood;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
  std::chrono::time_point<std::chrono::system_clock> beginTime = std::chrono::system_clock::now(), scoreTime;
  
  int scoreR{0};
  int scoreL{0};
  double foodDuration;

  void PlaceFood();
  void PlaceBonusFood();
  void Update(bool &running, double &gameDuration);
};

#endif