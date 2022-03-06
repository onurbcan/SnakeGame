#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "menu.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Menu menu;
  menu.InitialScreen();
  if(menu.CheckIfQuit()) {
    std::cout << "Game has terminated successfully!" <<std::endl;
    return 0;
  }
  while(true) {
    int diffLevel = menu.difficultyLevel;
    double gameDuration;

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight);
    game.Run(controller, renderer, kMsPerFrame, diffLevel, gameDuration);
    
    std::cout << "elapsed time: " << gameDuration << "s\n";


    menu.FinalScreen(game);
    if(menu.CheckIfQuit())
      break;
  }
  /*
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  */
  return 0;
}