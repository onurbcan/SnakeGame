#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::shared_ptr<Snake> const snakeR, std::shared_ptr<Snake> const snakeL, 
                SDL_Point const &food, SDL_Point const &bonusFood);
  void UpdateWindowTitle(int scoreR, int scoreL, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  // random device and variables initialezed to generate random colors for bonus food
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<Uint8> random_r;
  std::uniform_int_distribution<Uint8> random_g;
  std::uniform_int_distribution<Uint8> random_b;
};

#endif