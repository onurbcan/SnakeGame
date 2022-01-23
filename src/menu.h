#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>

enum Difficulties {
    Quit, Easy, Medium, Hard
};

class Menu {
    public:
        void InitialScreen();
        void FinalScreen();
        int CheckIfQuit();

    private:
        void AskName();
        void AskDifficultyLevel();
        std::string userName;
        int difficultyLevel{0};
        int ifQuit{0};
};

#endif