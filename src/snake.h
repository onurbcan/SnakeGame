#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"
#include "points.h"

class Snake : public Points {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(){}

  Snake(int &grid_width, int &grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  // copy constructor
  Snake(const Snake &other) {
    //std::cout << "copy constructor\n";
  }

  // destructor
  ~Snake() {
    //std::cout << "destructor\n";
  }

  // copy assignment operator
  Snake &operator=(const Points &other) {
    this->head_x = static_cast<float>(other.m_point.x);
    this->head_y = static_cast<float>(other.m_point.y);
    return *this;
  }

  // copy assignment operator
  Snake &operator=(const std::shared_ptr<Snake> &other) {
    this->head_x = other->head_x;
    this->head_y = other->head_y;
    return *this;
  }

  // move constructor
  Snake(Snake &&other) {
    //std::cout << "move constructor\n";
  }

  // move assignment operator
  Snake &operator=(Snake &&other) {
    //std::cout << "move assignment operator\n";
  }

  void Update(bool &isDead);

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.16f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell, bool &isDead);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif