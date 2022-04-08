#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      engine(dev()),
      random_r(0, static_cast<Uint8>(0xFF)),
      random_g(0, static_cast<Uint8>(0xFF)),
      random_b(0, static_cast<Uint8>(0xFF)) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::shared_ptr<Snake> const snakeR, std::shared_ptr<Snake> const snakeL, 
                        SDL_Point const &food, SDL_Point const &bonusFood) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  // yellow color
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render bonus food
  // color for bonus food changes each time randomly to give an idea about its limited time
  SDL_SetRenderDrawColor(sdl_renderer, random_r(engine), random_g(engine), random_b(engine), 0xFF);
  block.x = bonusFood.x * block.w;
  block.y = bonusFood.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snakeR's body
  // using blue color
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  for (SDL_Point const &point : snakeR->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snakeL's body
  // using forest green color
  SDL_SetRenderDrawColor(sdl_renderer, 0x22, 0x8B, 0x22, 0xFF);
  for (SDL_Point const &point : snakeL->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snakeR's head
  // using turquoise color
  block.x = static_cast<int>(snakeR->head_x) * block.w;
  block.y = static_cast<int>(snakeR->head_y) * block.h;
  if (snakeR->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x30, 0xD5, 0xC8, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }

  SDL_RenderFillRect(sdl_renderer, &block);
  
  // Render snakeL's head
  // using lime color
  block.x = static_cast<int>(snakeL->head_x) * block.w;
  block.y = static_cast<int>(snakeL->head_y) * block.h;
  if (snakeL->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }

  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int scoreR, int scoreL, int fps) {
  std::string title{"Blue Snake Score: " + std::to_string(scoreR) + 
                      " - Green Snake Score: " + std::to_string(scoreL) + 
                        " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
