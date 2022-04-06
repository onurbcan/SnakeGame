#include "menu.h"

void Menu::GameLoop() {
    std::size_t kFramesPerSecond{60};
    std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    std::size_t kScreenWidth{640};
    std::size_t kScreenHeight{640};
    std::size_t kGridWidth{32};
    std::size_t kGridHeight{32};

    InitialScreen();
    if(CheckIfQuit())
        return;
    File file;
    file.CheckFile(userName, lastHighestScore, highestScore);
    while(true) {
        std::shared_ptr<Controller> controller = std::make_shared<RightController>();
        std::shared_ptr<Controller> controller2 = std::make_shared<LeftController>();
        Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
        Game game(static_cast<int>(kGridWidth), static_cast<int>(kGridHeight));
        game.Run(controller, controller2, renderer, kMsPerFrame, difficultyLevel, gameDuration);
        file.AddData(userName, game.GetScore());
        file.CloseFile();
        std::cout << "elapsed time: " << gameDuration << "\n";
        std::cout << "last highest score: " << lastHighestScore << "\n";
        std::cout << "highest score: " << highestScore << "\n";
        FinalScreen();
        if(CheckIfQuit())
            return;
    }
    /*
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";
    */
    return;
}

void Menu::InitialScreen() {
    std::cout << "Welcome to Snake Game" << std::endl;
    AskName();
    AskDifficultyLevel();
    return;
}

void Menu::FinalScreen() {
    // Problem here because of the game object !
    //std::cout << userName << " has made " << game.GetScore() << " Score with the Size of " 
    //    << game.GetSize() << std::endl;
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
        std::cout << userName << " is an invalid name, please try again." << std::endl;
    }
    return;
}

void Menu::AskDifficultyLevel() {
    while(true) {
        std::cout << "Please enter the difficulty level of the game (e.g: 2):\n";
        std::cout << "Type 0 to quit.\n";
        std::cout << "Easy (1)\n";
        std::cout << "Medium (2)\n";
        std::cout << "Hard (3)\n";
        std::cin >> difficultyLevel;

        if (difficultyLevel == 0 || difficultyLevel == 1 || difficultyLevel == 2 || difficultyLevel == 3)
            break;
        std::cout << difficultyLevel << " is an invalid choice, please try again." << std::endl;
    }
    if(difficultyLevel == 0)
        ifQuit = 1;
    return;
}

int Menu::CheckIfQuit() {
    if(ifQuit == 1) {
        std::cout << "Game has terminated successfully!\n";
        return 1;
    }
    return 0;
}

std::string Menu::GetUserName() { return userName; }