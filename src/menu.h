#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <memory>
#include "game.h"
#include "snake.h"
#include "file.h"
#include "controller.h"
#include "renderer.h"
#include "SDL.h"

enum Difficulties {
    Quit, Easy, Medium, Hard
};

class Menu {
    public:
        void GameLoop();
        void InitialScreen();
        void FinalScreen();
        std::string GetUserName();
        int CheckIfQuit();
        int difficultyLevel{0};

    private:
        void AskName();
        void AskDifficultyLevel();
        std::string userName;
        int ifQuit{0};
        double gameDuration = 0.0;

        /*
        std::shared_ptr<Controller> controller = std::make_shared<RightController>();
        Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
        Game game(static_cast<int>(kGridWidth), static_cast<int>(kGridHeight));
        */
        int lastHighestScore = 0; // sample last highest score
        int highestScore = 0; // highest score of all users

};

#endif