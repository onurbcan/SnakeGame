#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  // Constructor
  Snake() {}
  
  // Constructor with parameters
  Snake(int &grid_width, int &grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}
  
  // Destructor
  ~Snake() {
  }

  // Copy constructor
  Snake(const Snake &other) {

  }

  // Copy assignment operator
  Snake &operator=(const Snake &other) {
    return *this;
  }

  // Move constructor
  Snake(Snake &&other) {

  }

  // Move assignment operator
  Snake &operator=(Snake &&other) {
    return *this;
  }

  void UpdateSingle();
  void UpdateMulti(float &otherSnakeHeadX, float &otherSnakeHeadY, std::vector<SDL_Point> &otherSnakeBody);
  void GrowBody();
  bool SnakeCell(int x, int y);
  int GetWinner();
  void SetSpeed(float speed) { this->speed = speed; }
  float GetSpeed() { return speed; }
  bool GetHeadDie() { return isHeadDie; }

  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  Direction direction = Direction::kUp;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBodySingle(SDL_Point &current_cell, SDL_Point &prev_cell);
  void UpdateBodyMulti(SDL_Point &current_cell, SDL_Point &prev_cell, 
          float &otherSnakeHeadX, float &otherSnakeHeadY, std::vector<SDL_Point> &otherSnakeBody);

  int grid_width;
  int grid_height;
  bool growing{false};
  float speed{0.16f}; // Speed set initially to the easy level's speed
  bool isHeadDie{false};
};

#endif