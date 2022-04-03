#include "game.h"
#include <iostream>
#include <vector>
#include "SDL.h"

Game::Game(int grid_width, int grid_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  snake = std::make_shared<Snake>(grid_width, grid_height);
  snake2 = std::make_shared<Snake>(grid_width, grid_height);
  food = std::make_shared<Points>(0xFF, 0xCC, 0x00, 0xFF);
  bonusFood = std::make_shared<Points>(0x55, 0x55, 0x55, 0xFF);
  //allPoints = std::make_shared<std::shared_ptr<Points>>();

  snake2->head_x = (grid_width / 4);
  snake2->head_y = (grid_height / 4);
  snake2->direction = Snake::Direction::kDown;

  allPoints.push_back(food);
  allPoints.push_back(bonusFood);
  allPoints.push_back(snake);
  allPoints.push_back(snake2);

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

  snake->speed = (diffLevel + 3) * 0.04; //gets values of 0.16, 0.20 and 0.24 
                                        //depending on diff level
  //std::cout << "snake speed: " << snake->speed << " , diff level: " << diffLevel << "\n";
  startTime = std::chrono::system_clock::now();

  while (running) {
    frame_start = SDL_GetTicks();
    //std::cout << "snake speed: " << snake->speed << "\n";
    //std::cout << "snake2 speed: " << snake2->speed << "\n";

    // Input, Update, Render - the main game loop.

    controllerR->HandleInput(running, snake);
    //controllerL->HandleInput(running, snake2);
    Update(gameDuration);
    //renderer.Render(snake, food, bonusFood);
    renderer.Render(allPoints);
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
    if (!snake->SnakeCell(x, y)) {
      food->m_point.x = x;
      food->m_point.y = y;
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
    if (!(snake->SnakeCell(x, y) && x == food->m_point.x && y == food->m_point.y)) {
      bonusFood->m_point.x = x;
      bonusFood->m_point.y = y;
      break;
    }
  }
  return;
}

void Game::Update(double &gameDuration) {
  bool isDead = false;
  
  if (!snake->alive) return;
  if (!snake2->alive) return;

  snake->Update(isDead);
  snake2->Update(isDead);
  if(isDead) {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    gameDuration = elapsedSeconds.count();
  }

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  scoreTime = std::chrono::system_clock::now();
  std::chrono::duration<double> foodElapsedSeconds = scoreTime - beginTime;
  foodDuration = foodElapsedSeconds.count();
  //std::cout << foodDuration << std::endl;
  if (foodDuration > 5.0) {
    beginTime = std::chrono::system_clock::now();
    PlaceBonusFood();
  }
  // Check if there's food over here
  if (bonusFood->m_point.x == new_x && bonusFood->m_point.y == new_y) {
    beginTime = std::chrono::system_clock::now();
    score++;
    PlaceBonusFood();
  }

  // Check if there's food over here
  if (food->m_point.x == new_x && food->m_point.y == new_y) {
    score++;
    scoreTime = std::chrono::system_clock::now();
    PlaceFood();

    // Grow snake and increase speed.
    snake->GrowBody();
    //snake->speed += 0.02;

    snake2->GrowBody();
    //snake2->speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }