#include "menu.h"

void Menu::GameLoop() {
    std::size_t kFramesPerSecond{60};
    std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    std::size_t kScreenWidth{640};
    std::size_t kScreenHeight{640};
    std::size_t kGridWidth{32};
    std::size_t kGridHeight{32};

    InitialScreen();
    if(CheckIsQuit())
        return;
    File file;
    file.CheckFile(userNameR, userNameL, lastHighestScoreR, lastHighestScoreL, highestScore);
    while(true) {
        std::shared_ptr<Controller> controllerR = std::make_shared<RightController>();
        std::shared_ptr<Controller> controllerL = std::make_shared<LeftController>();
        Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
        Game game(static_cast<int>(kGridWidth), static_cast<int>(kGridHeight));
        game.Run(controllerR, controllerL, renderer, kMsPerFrame, difficultyLevelR, difficultyLevelL, gameDuration);
        file.AddData(userNameR, userNameL, game.GetScoreR(), game.GetScoreL());
        if(game.GetWinner())
            std::cout << "winner: Blue Snake\n";
        else
            std::cout << "winner: Green Snake\n";
        std::cout << "elapsed time: " << gameDuration << "\n";
        std::cout << "last highest score user R: " << lastHighestScoreR << "\n";
        std::cout << "last highest score user L: " << lastHighestScoreL << "\n";
        std::cout << "highest score: " << highestScore << "\n";
        FinalScreen();
        if(CheckIsQuit())
            return;
    }
    return;
}

void Menu::InitialScreen() {
    std::cout << "Welcome to Snake Game\n";
    AskName();
    AskDifficultyLevel();
    return;
}

void Menu::FinalScreen() {
    AskDifficultyLevel();
    return;
}

void Menu::AskName() {
    while(true) {
        std::cout << "Please enter first user's name (at least 4 characters):\n";
        std::cin >> userNameR;
        if (userNameR.size() >= 4)
            break;
        std::cout << userNameR << " is an invalid name, please try again.\n";
    }
    while(true) {
        std::cout << "Please enter second user's name (at least 4 characters):\n";
        std::cin >> userNameL;
        if (userNameL.size() >= 4)
            break;
        std::cout << userNameL << " is an invalid name, please try again.\n";
    }
    return;
}

void Menu::AskDifficultyLevel() {
    std::string userName{""};
    while(isQuit != 1) {
        userName = "first";
        PrintAskDifficultyLevelLines(userName);
        std::cin >> difficultyLevelR;
        // If submitted difficulty level is valid, while loop is broken
        if(CheckDifficultyLevel(difficultyLevelR))
            break;
    }
    while(isQuit != 1) {
        userName = "second";
        PrintAskDifficultyLevelLines(userName);
        std::cin >> difficultyLevelL;
        // If submitted difficulty level is valid, while loop is broken
        if(CheckDifficultyLevel(difficultyLevelL))
            break;
    }
    return;
}

void Menu::PrintAskDifficultyLevelLines(std::string &userName) {
    std::cout << "Please enter the difficulty level for the " << userName << " user (e.g: 2):\n";
    std::cout << "Type 0 to quit.\n";
    std::cout << "Easy (1)\n";
    std::cout << "Medium (2)\n";
    std::cout << "Hard (3)\n";
    return;
}

bool Menu::CheckDifficultyLevel(int &difficultyLevel) {
    if(difficultyLevel == 0) {
        isQuit = 1;
        return true;
    }
    // Each condition is written seperately to make sure a valid level is submitted
    if(difficultyLevel == 1 || difficultyLevel == 2 || difficultyLevel == 3)
        return true;
    std::cout << difficultyLevel << " is an invalid choice, please try again.\n";
    return false;
}

int Menu::CheckIsQuit() {
    if(isQuit == 1) {
        std::cout << "Game has terminated successfully!\n";
        return 1;
    }
    return 0;
}
