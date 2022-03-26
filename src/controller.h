#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  virtual void HandleInput(bool &running, Snake &snake) const = 0;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

class RightController : public Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;

};

#endif