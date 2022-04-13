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

class Menu {
    public:
        Menu() {}
        void GameLoop();
        void InitialScreen();
        void FinalScreen(int winner, int scoreR, int scoreL);
        std::string GetUserNameR() { return userNameR; }
        std::string GetUserNameL() { return userNameL; }

    private:
        void AskGameMode();
        void AskName();
        void AskDifficultyLevel();
        void PrintAskDifficultyLevelLines(std::string &userName);
        bool CheckDifficultyLevel(int &difficultyLevel);

        int gameMode{0};
        std::string userNameR{""}, userNameL{""};
        int difficultyLevelR{0}, difficultyLevelL{0};
        int isQuit{0}; // Variable to check if the user wants to quit in menus
        double gameDuration = 0.0; // Game duration after conversion to double type
        int lastHighestScoreR = 0, lastHighestScoreL = 0; // Last highest score of user R and user L
        int highestScore; // Highest score of all users
};

#endif