#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "snake.h"

class ControllerABS {
 public:
  virtual void HandleInput(bool &running, std::shared_ptr<Snake> &snake) const = 0;
};

class Controller : public ControllerABS {
 public:
  virtual void HandleInput(bool &running, std::shared_ptr<Snake> &snake) const {};

  virtual void ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

class RightController : public Controller {
 public:
  void HandleInput(bool &running, std::shared_ptr<Snake> &snake) const;
};

class LeftController : public Controller {
 public:
  void HandleInput(bool &running, std::shared_ptr<Snake> &snake2) const;
};

#endif