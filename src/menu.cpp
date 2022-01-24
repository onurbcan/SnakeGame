#include "menu.h"

void Menu::InitialScreen() {
    std::cout << "Welcome to Snake Game" << std::endl;
    AskName();
    AskDifficultyLevel();
    return;
}
void Menu::FinalScreen(Game &game) {
    std::cout << "Game has terminated successfully!" <<std::endl;
    std::cout << userName << "has made " << game.GetScore() << "Score with the Size of " 
        << game.GetSize() << std::endl;
    AskDifficultyLevel();
    return;
}

void Menu::AskName() {
    while(true) {
        userName = "";
        std::cout << "Please enter your name (at least 4 characters):" << std::endl;
        std::cin >> userName;
        if (userName.size() >= 4)
            break;
        std::cout << userName << "is an invalid name, please try again." << std::endl;
    }
    return;
}

void Menu::AskDifficultyLevel() {
    while(true) {
        std::cout << "Please enter the difficulty level of the game (e.g: 2):" << std::endl;
        std::cout << "Type 0 to quit." << std::endl;
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
        difficultyLevel = Difficulties::Easy;
        break;
    case Difficulties::Medium:
        difficultyLevel = Difficulties::Medium;
        break;
    case Difficulties::Hard:
        difficultyLevel = Difficulties::Hard;
        break;
    default:
        break;
    }
    return;
}

int Menu::CheckIfQuit() {
    if(ifQuit == 1)
        return 1;
    return 0;
}