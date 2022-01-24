#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

int Controller::HandleInput(bool &running, Snake &snake1, Snake &snake2) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        // Player #1
        case SDLK_UP:
          ChangeDirection(snake1, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake1, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake1, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake1, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;

        // Player #2
        case SDLK_w:
          ChangeDirection(snake2, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_s:
          ChangeDirection(snake2, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_a:
          ChangeDirection(snake2, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_d:
          ChangeDirection(snake2, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;

        // ESC key
        case SDLK_ESCAPE:
          return (1);
          break;
      }
    }
  }
}