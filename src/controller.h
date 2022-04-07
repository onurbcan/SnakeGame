#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "snake.h"

class ControllerABS {
 public:
  virtual void HandleInput(bool &running, std::shared_ptr<Snake> &snake, SDL_Event e) const = 0;
};

class Controller : public ControllerABS {
 public:
  virtual void HandleInput(bool &running, std::shared_ptr<Snake> &snake, SDL_Event e) const {};

  virtual void ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

class RightController : public Controller {
 public:
  void HandleInput(bool &running, std::shared_ptr<Snake> &snake, SDL_Event e) const;
};

class LeftController : public Controller {
 public:
  void HandleInput(bool &running, std::shared_ptr<Snake> &snake2, SDL_Event e) const;
};

#endif