#include "renderer.h"
#include "snake.h"
#include <iostream>
#include <memory>
#include <string>
/*
void operator=(std::shared_ptr<Snake> &s1, std::shared_ptr<Snake> &s2) {
  s1->head_x = s2->head_x;
  s1->head_y = s2->head_y;
    return *this;
}
*/
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
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

void Renderer::Render(std::vector<std::shared_ptr<Points>> &snake) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  //std::shared_ptr<Snake> tempSnake = std::make_shared<Snake>();
  for(auto i : snake) {
    // Render snake's head

    auto tempSnake = std::dynamic_pointer_cast<std::shared_ptr<Snake>>(std::static_pointer_cast<Points>(i));
    block.x = i->m_point.x * block.w;
    block.y = i->m_point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    if(tempSnake) {
      // snake
      /*if (tempSnake->alive) {
        tempSnake->m_color[0] = 0x00;
        tempSnake->m_color[1] = 0x7A;
        tempSnake->m_color[2] = 0xCC;
        tempSnake->m_color[3] = 0xFF;
      } else {
        tempSnake->m_color[0] = 0xFF;
        tempSnake->m_color[1] = 0x00;
        tempSnake->m_color[2] = 0x00;
        tempSnake->m_color[3] = 0xFF;
      }*/
      std::cout << "if cond\n";
    }
    SDL_SetRenderDrawColor(sdl_renderer, i->m_color[0], i->m_color[1], i->m_color[2], i->m_color[3]);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

/*
void Renderer::Render(std::shared_ptr<Snake> const snake, SDL_Point const &food, SDL_Point const &bonusFood) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render bonus food
  SDL_SetRenderDrawColor(sdl_renderer, 0x55, 0x55, 0x55, 0xFF);
  block.x = bonusFood.x * block.w;
  block.y = bonusFood.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}
*/
void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
