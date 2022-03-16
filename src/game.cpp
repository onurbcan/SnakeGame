#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
  scoreTime = std::chrono::system_clock::now();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration, int diffLevel, double &gameDuration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  snake.speed = (diffLevel + 3) * 0.04; //gets values of 0.16, 0.20 and 0.24 
                                        //depending on diff level

  startTime = std::chrono::system_clock::now();
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update(gameDuration);
    renderer.Render(snake, food, bonusFood);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      break;
    }
  }
  return;
}

void Game::PlaceBonusFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    if (!(snake.SnakeCell(x, y) && x != food.x && y != food.y)) {
      bonusFood.x = x;
      bonusFood.y = y;
      break;
    }
  }
  return;
}

void Game::Update(double &gameDuration) {
  bool isDead = false;
  
  if (!snake.alive) {
    return;
  }

  snake.Update(isDead);
  if(isDead) {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    gameDuration = elapsedSeconds.count();
  }

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (bonusFood.x == new_x && bonusFood.y == new_y) {
    score++;
    
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    scoreTime = std::chrono::system_clock::now();
    PlaceFood();
    PlaceBonusFood();

    beginTime = std::chrono::system_clock::now();
    // Grow snake and increase speed.
    snake.GrowBody();
  }
  if() {
    scoreTime = std::chrono::system_clock::now();
    std::chrono::duration<double> foodElapsedSeconds = scoreTime - beginTime;
    foodDuration = foodElapsedSeconds.count();
    std::cout << foodDuration << std::endl;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }