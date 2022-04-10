#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(int grid_width, int grid_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  snakeR = std::make_shared<Snake>(grid_width, grid_height);
  snakeL = std::make_shared<Snake>(grid_width, grid_height);
  
  snakeL->head_x = (grid_width / 4);
  snakeL->head_y = (grid_height / 4);
  snakeL->direction = Snake::Direction::kDown;
  
  PlaceFood();
  PlaceBonusFood();
  scoreTime = std::chrono::system_clock::now();
}

void Game::Run(std::shared_ptr<Controller> const &controllerR, 
               std::shared_ptr<Controller> const &controllerL, Renderer &renderer,
               std::size_t target_frame_duration, int diffLevel, double &gameDuration) {

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  snakeR->setSpeed((diffLevel + 3) * 0.04); //has values of 0.16, 0.20 and 0.24 
                                        //depending on diff level
  snakeL->setSpeed((diffLevel + 3) * 0.04); //has values of 0.16, 0.20 and 0.24 
                                        //depending on diff level

  startTime = std::chrono::system_clock::now();

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    SDL_Event e;
    SDL_PollEvent(&e);
    controllerR->HandleInput(running, snakeR, e);
    controllerL->HandleInput(running, snakeL, e);
    Update(running, gameDuration);
    renderer.Render(snakeR, snakeL, food, bonusFood);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(scoreR, scoreL, frame_count);
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
    if (!(snakeR->SnakeCell(x, y) && snakeL->SnakeCell(x, y))) {
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
    if (!(snakeR->SnakeCell(x, y) && snakeL->SnakeCell(x, y) && x == food.x && y == food.y)) {
      bonusFood.x = x;
      bonusFood.y = y;
      break;
    }
  }
  return;
}

void Game::Update(bool &running, double &gameDuration) {
  if(!(running && snakeR->alive && snakeL->alive)) {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    gameDuration = elapsedSeconds.count();
    return;
  }

  snakeR->Update(snakeL->head_x, snakeL->head_y, snakeL->body);
  if(!(running && snakeR->alive && snakeL->alive)) {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    gameDuration = elapsedSeconds.count();
    return;
  }
  
  snakeL->Update(snakeR->head_x, snakeR->head_y, snakeR->body);
  if(!(running && snakeR->alive && snakeL->alive)) {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    gameDuration = elapsedSeconds.count();
    return;
  }

  // snakeR's position
  int new_xR = static_cast<int>(snakeR->head_x);
  int new_yR = static_cast<int>(snakeR->head_y);

  // snakeL's position
  int new_xL = static_cast<int>(snakeL->head_x);
  int new_yL = static_cast<int>(snakeL->head_y);

  scoreTime = std::chrono::system_clock::now();
  std::chrono::duration<double> foodElapsedSeconds = scoreTime - beginTime;
  foodDuration = foodElapsedSeconds.count();

  if (foodDuration > 5.0) {
    beginTime = std::chrono::system_clock::now();
    PlaceBonusFood();
  }

  // check if bonus food is eaten by snakeR
  if (bonusFood.x == new_xR && bonusFood.y == new_yR) {
    beginTime = std::chrono::system_clock::now();
    ++scoreR;
    PlaceBonusFood();
  }

  // check if food is eaten by snakeR
  if (food.x == new_xR && food.y == new_yR) {
    scoreTime = std::chrono::system_clock::now();
    ++scoreR;
    PlaceFood();
    snakeR->GrowBody();
  }

  // check if bonus food is eaten by snakeL
  if (bonusFood.x == new_xL && bonusFood.y == new_yL) {
    beginTime = std::chrono::system_clock::now();
    ++scoreL;
    PlaceBonusFood();
  }

  // check if food is eaten by snakeL
  if (food.x == new_xL && food.y == new_yL) {
    scoreTime = std::chrono::system_clock::now();
    ++scoreL;
    PlaceFood();
    snakeL->GrowBody();
  }
  return;
}

int Game::GetScoreR() const { return scoreR; }
int Game::GetScoreL() const { return scoreL; }
int Game::GetSizeR() const { return snakeR->size; }
int Game::GetSizeL() const { return snakeL->size; }

int Game::GetWinner() const {
  // Winner is selected depending on score if head crash occurs
  if(snakeL->getHeadDie() || snakeR->getHeadDie())
    return scoreR > scoreL ? 1 : 0;
  // Otherwise alive status
  return snakeR->alive ? 1 : 0; }