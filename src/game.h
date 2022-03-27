#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(int grid_width, int grid_height);
  void Run(std::shared_ptr<Controller> const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 //private:
  std::shared_ptr<Snake> snake;// = std::make_shared<Snake>(std::size_t, std::size_t);
  //Snake snake2;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif