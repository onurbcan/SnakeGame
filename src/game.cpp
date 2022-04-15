#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(int grid_width, int grid_height, int difficultyLevelR)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      difficultyLevelR(difficultyLevelR) {
  snakeR = std::make_shared<Snake>(grid_width, grid_height);
  
  PlaceFoodSingle();
  PlaceBonusFoodSingle();
  scoreTime = std::chrono::system_clock::now();
}

Game::Game(int grid_width, int grid_height, int difficultyLevelR, int difficultyLevelL)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      difficultyLevelR(difficultyLevelR),
      difficultyLevelL(difficultyLevelL) {
  snakeR = std::make_shared<Snake>(grid_width, grid_height);
  snakeL = std::make_shared<Snake>(grid_width, grid_height);
  
  snakeL->head_x = (grid_width / 4);
  snakeL->head_y = (grid_height / 4);
  snakeL->direction = Snake::Direction::kDown;
  
  PlaceFoodMulti();
  PlaceBonusFoodMulti();
  scoreTime = std::chrono::system_clock::now();
}

void Game::RunSingle(std::shared_ptr<Controller> const &controllerR,
                Renderer &renderer, std::size_t target_frame_duration, double &gameDuration) {

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  snakeR->setSpeed((difficultyLevelR + 3) * 0.04); // Speed for right user is set from the values of 0.16, 0.20 and 0.24 
                                                  //depending on right user's difficulty level

  startTime = std::chrono::system_clock::now(); // Beginning of the game

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    // SDL_Events are sent to controllerR
    SDL_Event e;
    SDL_PollEvent(&e);
    controllerR->HandleInput(running, snakeR, e);
    UpdateSingle(running, gameDuration);
    renderer.RenderSingle(snakeR, food, bonusFood);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitleSingle(scoreR, frame_count);
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

void Game::RunMulti(std::shared_ptr<Controller> const &controllerR, std::shared_ptr<Controller> const &controllerL, 
                Renderer &renderer, std::size_t target_frame_duration, double &gameDuration) {

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  snakeR->setSpeed((difficultyLevelR + 3) * 0.04); // Speed for right user is set from the values of 0.16, 0.20 and 0.24 
                                                  //depending on right user's difficulty level
  snakeL->setSpeed((difficultyLevelL + 3) * 0.04); // Speed for left user is set from the values of 0.16, 0.20 and 0.24 
                                        //depending on left user's difficulty level

  startTime = std::chrono::system_clock::now(); // Beginning of the game

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    // SDL_Events are sent both controllerR and controllerL not to lose any event in any of the controller section
    SDL_Event e;
    SDL_PollEvent(&e);
    controllerR->HandleInput(running, snakeR, e);
    controllerL->HandleInput(running, snakeL, e);
    UpdateMulti(running, gameDuration);
    renderer.RenderMulti(snakeR, snakeL, food, bonusFood);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitleMulti(scoreR, scoreL, frame_count);
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

void Game::PlaceFoodSingle() {
  int x, y;
  while(true) {
    x = random_w(engine);
    y = random_h(engine);
    // Checks if the location is not occupied by snake item before placing
    // food
    if(!(snakeR->SnakeCell(x, y))) {
      food.x = x;
      food.y = y;
      break;
    }
  }
  return;
}

void Game::PlaceBonusFoodSingle() {
  int x, y;
  while(true) {
    x = random_w(engine);
    y = random_h(engine);
    // Checks if the location is not occupied by snake and food items before placing
    // bonus food
    if(!(snakeR->SnakeCell(x, y) && x == food.x && y == food.y)) {
      bonusFood.x = x;
      bonusFood.y = y;
      break;
    }
  }
  return;
}

void Game::PlaceFoodMulti() {
  int x, y;
  while(true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if(!(snakeR->SnakeCell(x, y) && snakeL->SnakeCell(x, y))) {
      food.x = x;
      food.y = y;
      break;
    }
  }
  return;
}

void Game::PlaceBonusFoodMulti() {
  int x, y;
  while(true) {
    x = random_w(engine);
    y = random_h(engine);
    if(!(snakeR->SnakeCell(x, y) && snakeL->SnakeCell(x, y) && x == food.x && y == food.y)) {
      bonusFood.x = x;
      bonusFood.y = y;
      break;
    }
  }
  return;
}

void Game::UpdateSingle(bool &running, double &gameDuration) {
  // Checks if the game is over
  if(!(running && snakeR->alive)) {
    running = false;
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    gameDuration = elapsedSeconds.count();
    return;
  }
  snakeR->UpdateSingle();

  // snakeR's position
  int new_xR = static_cast<int>(snakeR->head_x);
  int new_yR = static_cast<int>(snakeR->head_y);

  scoreTime = std::chrono::system_clock::now();
  std::chrono::duration<double> foodElapsedSeconds = scoreTime - beginTime;
  bonusFoodDuration = foodElapsedSeconds.count();

  if (bonusFoodDuration > 5.0) {
    beginTime = std::chrono::system_clock::now();
    PlaceBonusFoodSingle();
  }

  // check if bonus food is eaten by snakeR
  if (bonusFood.x == new_xR && bonusFood.y == new_yR) {
    beginTime = std::chrono::system_clock::now();
    ++scoreR;
    PlaceBonusFoodSingle();
  }

  // check if food is eaten by snakeR
  if (food.x == new_xR && food.y == new_yR) {
    scoreTime = std::chrono::system_clock::now();
    ++scoreR;
    PlaceFoodSingle();
    snakeR->GrowBody();
  }
  return;
}

void Game::UpdateMulti(bool &running, double &gameDuration) {
  // Checks if the game is over
  if(!(running && snakeR->alive && snakeL->alive)) {
    running = false;
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    gameDuration = elapsedSeconds.count();
    return;
  }
  snakeR->UpdateMulti(snakeL->head_x, snakeL->head_y, snakeL->body);  
  snakeL->UpdateMulti(snakeR->head_x, snakeR->head_y, snakeR->body);

  // snakeR's position
  int new_xR = static_cast<int>(snakeR->head_x);
  int new_yR = static_cast<int>(snakeR->head_y);

  // snakeL's position
  int new_xL = static_cast<int>(snakeL->head_x);
  int new_yL = static_cast<int>(snakeL->head_y);

  scoreTime = std::chrono::system_clock::now();
  std::chrono::duration<double> foodElapsedSeconds = scoreTime - beginTime;
  bonusFoodDuration = foodElapsedSeconds.count();

  if (bonusFoodDuration > 5.0) {
    beginTime = std::chrono::system_clock::now();
    PlaceBonusFoodMulti();
  }

  // check if bonus food is eaten by snakeR
  if (bonusFood.x == new_xR && bonusFood.y == new_yR) {
    beginTime = std::chrono::system_clock::now();
    ++scoreR;
    PlaceBonusFoodMulti();
  }

  // check if food is eaten by snakeR
  if (food.x == new_xR && food.y == new_yR) {
    scoreTime = std::chrono::system_clock::now();
    ++scoreR;
    PlaceFoodMulti();
    snakeR->GrowBody();
  }

  // check if bonus food is eaten by snakeL
  if (bonusFood.x == new_xL && bonusFood.y == new_yL) {
    beginTime = std::chrono::system_clock::now();
    ++scoreL;
    PlaceBonusFoodMulti();
  }

  // check if food is eaten by snakeL
  if (food.x == new_xL && food.y == new_yL) {
    scoreTime = std::chrono::system_clock::now();
    ++scoreL;
    PlaceFoodMulti();
    snakeL->GrowBody();
  }
  return;
}

int Game::GetWinner() const {
  // Winner is selected depending on score if head crash occurs
  if(snakeL->getHeadDie() || snakeR->getHeadDie())
    return scoreR > scoreL ? 1 : 2;
  // Otherwise alive status
  return snakeR->alive ? 1 : 2;
}