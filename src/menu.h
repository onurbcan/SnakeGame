#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <memory>
#include "SDL.h"
#include "game.h"
#include "snake.h"
#include "file.h"
#include "controller.h"
#include "renderer.h"

class Menu {
    public:
        Menu() {}
        void GameLoop();
        void GameLoopSingle();
        void GameLoopMulti();
        void InitialScreen();
        void FinalScreenSingle(int scoreR);
        void FinalScreenMulti(int winner, int scoreR, int scoreL);
        void DisplayGameDuration();
        std::string GetUserNameR() { return userNameR; }
        std::string GetUserNameL() { return userNameL; }

    private:
        void AskGameMode();
        void AskName();
        void AskDifficultyLevel();
        void PrintAskDifficultyLevelLines(std::string &userName);
        bool CheckDifficultyLevel(int &difficultyLevel);

        File file;
        int gameMode{0};
        std::string userNameR{""}, userNameL{""};
        int difficultyLevelR{0}, difficultyLevelL{0};
        int isQuit{0}; // Variable to check if the user wants to quit in menus
        double gameDuration = 0.0; // Game duration after conversion to double type
        int lastHighestScoreR = 0, lastHighestScoreL = 0; // Last highest score of user R and user L
        int highestScore; // Highest score of all users
        std::size_t kFramesPerSecond{60};
        std::size_t kMsPerFrame{1000 / kFramesPerSecond};
        std::size_t kScreenWidth{640};
        std::size_t kScreenHeight{640};
        std::size_t kGridWidth{32};
        std::size_t kGridHeight{32};
};

#endif