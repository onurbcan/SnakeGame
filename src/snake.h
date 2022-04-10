#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"

class Snake {
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
  Snake &operator=(const Snake &other) {
    //std::cout << "copy assignment operator\n";
    return *this;
  }

  // move constructor
  Snake(Snake &&other) {
    this->direction = Direction::kDown;
    //std::cout << "move constructor\n";
  }

  // move assignment operator
  Snake &operator=(Snake &&other) {
    this->direction = Direction::kDown;
    //std::cout << "move assignment operator\n";
  }

  void Update(float &otherSnakeHeadX, float &otherSnakeHeadY, std::vector<SDL_Point> &otherSnakeBody);

  void GrowBody();
  bool SnakeCell(int x, int y);
  int GetWinner();

  void setSpeed(float speed) { this->speed = speed; }
  float getSpeed() { return speed; }
  bool getHeadDie() { return isHeadDie; }

  Direction direction = Direction::kUp;

  
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell, 
          float &otherSnakeHeadX, float &otherSnakeHeadY, std::vector<SDL_Point> &otherSnakeBody);

  bool growing{false};
  int grid_width;
  int grid_height;

  float speed{0.16f};
  bool isHeadDie{false};
};

#endif