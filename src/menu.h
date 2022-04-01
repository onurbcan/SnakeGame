#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "game.h"

enum Difficulties {
    Quit, Easy, Medium, Hard
};

class Menu {
    public:
        void InitialScreen();
        void FinalScreen(Game &game);
        std::string GetUserName();
        int CheckIfQuit();
        int difficultyLevel{0};

    private:
        void AskName();
        void AskDifficultyLevel();
        std::string userName;
        int ifQuit{0};
};

#endif