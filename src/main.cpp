#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "file.h"
#include <string>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::string newUserName = "user2"; //sample user name to test the compare ability of the file.cpp methods
  int lastScore = 0;
  File file;
  file.CheckFile(newUserName, lastScore);
  file.AddData();
  std::cout << lastScore << std::endl;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}