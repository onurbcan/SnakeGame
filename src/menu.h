#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>

enum Difficulties {
    Quit, Easy, Medium, Hard
}

class Menu {
    public:
        void InitialScreen();
        void FinalScreen();
    private:
        void AskName();
        void AskDifficultyLevel();
        void CheckIfQuit();
        std::string userName;
        int difficultyLevel{0};
        int ifQuit{0};
}

#endif