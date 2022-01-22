#include "menu.h"
#include "game.h"

Menu::InitialScreen() {
    std::cout << "Welcome to Snake Game" << std::endl;
    AskName();
    AskDifficultyLevel();
    CheckIfQuit();
    return;
}
Menu::FinalScreen() {
    AskDifficultyLevel();
    CheckIfQuit();
    return;
}

Menu::AskName() {
    while(true) {
        userName = "";
        std::cout << "Please enter your name (at least 4 characters):" << std::endl;
        std::cin >> userName;
        if (userName.size() >= 4)
            break;
        std::cout << userName << "is an invalid name, please try again." << std::endl;
    }
}

Menu::AskDifficultyLevel() {
    while(true) {
        std::cout << "Please enter the difficulty level of the game (e.g: 2):" << std::endl;
        std::cout << "Type 0 to quit."
        std::cout << "Easy (1)" << std::endl;
        std::cout << "Medium (2)" << std::endl;
        std::cout << "Hard (3)" << std::endl;
        std::cin >> difficultyLevel;

        if (0 <= difficultyLevel && difficultyLevel <= 3)
            break;
        std::cout << difficultyLevel << "is an invalid choice, please try again." << std::endl;
    }
    switch (difficultyLevel) {
    case Difficulties::Quit:
        ifQuit = 1;
        break;
    case Difficulties::Easy:
        break;
    case Difficulties::Medium:
        break;
    case Difficulties::Hard:
        break;
    default:
        break;
    }
}

void Menu::CheckIfQuit() {
    return;
}