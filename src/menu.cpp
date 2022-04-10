#include "menu.h"

void Menu::GameLoop() {
    std::size_t kFramesPerSecond{60};
    std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    std::size_t kScreenWidth{640};
    std::size_t kScreenHeight{640};
    std::size_t kGridWidth{32};
    std::size_t kGridHeight{32};

    InitialScreen();
    if(isQuit) {
        std::cout << "Game has terminated successfully!\n";
        return;
    }
    File file;
    while(true) {
        file.CheckFile(userNameR, userNameL, lastHighestScoreR, lastHighestScoreL, highestScore);
        std::shared_ptr<Controller> controllerR = std::make_shared<RightController>();
        std::shared_ptr<Controller> controllerL = std::make_shared<LeftController>();
        Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
        Game game(static_cast<int>(kGridWidth), static_cast<int>(kGridHeight));
        game.Run(controllerR, controllerL, renderer, kMsPerFrame, difficultyLevelR, difficultyLevelL, gameDuration);
        file.AddData(userNameR, userNameL, game.GetScoreR(), game.GetScoreL());
        FinalScreen(game.GetWinner(), game.GetScoreR(), game.GetScoreL());
        if(isQuit) {
            std::cout << "Game has terminated successfully!\n";
            break;
        }
    }
    return;
}

void Menu::InitialScreen() {
    std::cout << "Welcome to Snake Game\n";

    AskName();
    AskDifficultyLevel();
    return;
}

void Menu::FinalScreen(int winner, int scoreR, int scoreL) {
    std::cout << "Game Over!\n";
    std::cout << "Winner is ";
    // 1 represents right user and 2 left user, which are coming from the method in Game class GetWinner 
    switch(winner) {
        case 1:
            std::cout << userNameR << " with the score of " << scoreR;
            std::cout << " and " << userNameL << " has the score of " << scoreL << ".\n";
            break;
        case 2:
            std::cout << userNameL << " with the score of " << scoreL;
            std::cout << " and " << userNameR << " has the score of " << scoreR << ".\n";
            break;
        default:
            break;
    }
    if(scoreR > highestScore)
        std::cout << userNameR << " has made a new record!\n";
    else if(scoreR > lastHighestScoreR)
        std::cout << userNameR << " has made his/her highest score!\n";
    if(scoreL > highestScore)
        std::cout << userNameL << " has made a new record!\n";
    else if(scoreL > lastHighestScoreL)
        std::cout << userNameL << " has made his/her highest score!\n";
    gameDuration *= 100;
    gameDuration = static_cast<int>(gameDuration);
    gameDuration /= 100.0;
    std::cout << "Game duration was " << gameDuration << " seconds.\n";
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
