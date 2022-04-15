#include "menu.h"

void Menu::GameLoop() {
    while(true) {
        InitialScreen();
        switch(gameMode) {
        case 0:
            // Quit
            break;
        case 1:
            // Singleplayer
            GameLoopSingle();
            break;
        case 2:
            // Multiplayer
            GameLoopMulti();
            break;
        default:
            break;
        }
        if(isQuit) {
            std::cout << "Game has terminated successfully!\n";
            break;
        }
    }
    return;
}

void Menu::GameLoopSingle() {
    file.CheckFile(userNameR, userNameL, lastHighestScoreR, lastHighestScoreL, highestScore);
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    std::shared_ptr<Controller> controllerR = std::make_shared<RightController>();
    Game game(static_cast<int>(kGridWidth), static_cast<int>(kGridHeight), difficultyLevelR);
    game.RunSingle(controllerR, renderer, kMsPerFrame, gameDuration);
    file.AddDataSingle(userNameR, game.GetScoreR());
    FinalScreenSingle(game.GetScoreR());
    return;
}

void Menu::GameLoopMulti() {
    file.CheckFile(userNameR, userNameL, lastHighestScoreR, lastHighestScoreL, highestScore);
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    std::shared_ptr<Controller> controllerR = std::make_shared<RightController>();
    std::shared_ptr<Controller> controllerL = std::make_shared<LeftController>();
    Game game(static_cast<int>(kGridWidth), static_cast<int>(kGridHeight), difficultyLevelR, difficultyLevelL);
    game.RunMulti(controllerR, controllerL, renderer, kMsPerFrame, gameDuration);
    file.AddDataMulti(userNameR, userNameL, game.GetScoreR(), game.GetScoreL());
    FinalScreenMulti(game.GetWinner(), game.GetScoreR(), game.GetScoreL());
    return;
}

void Menu::InitialScreen() {
    std::cout << "Welcome to Snake Game\n";
    AskGameMode();
    system("clear");
    AskName();
    system("clear");
    AskDifficultyLevel();
    system("clear");
    return;
}

void Menu::AskGameMode() {
    do {
        std::cout << "How would you like to play the game? Please enter the relevant number.\n";
        std::cout << "Type 0 to quit.\n";
        std::cout << "Singleplayer (1)\n";
        std::cout << "Multiplayer (2)\n";
        std::cin >> gameMode;        
        if(gameMode == 0)
            isQuit = 1;
    } while(!(gameMode == 0 || gameMode == 1 || gameMode == 2));
    return;
}

void Menu::AskName() {
    switch (gameMode) {
    case 0:
        // Quit
        break;
    case 1:
        // Singleplayer
        while(true) {
            std::cout << "Please enter your user name (at least 4 characters):\n";
            std::cin >> userNameR;
            if (userNameR.size() >= 4)
                break;
            std::cout << userNameR << " is an invalid name, please try again.\n";
        }
        break;
    case 2:
        // Multiplayer
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
            if (userNameL.size() >= 4 && userNameL.compare(userNameR) != 0)
                break;
            std::cout << userNameL << " is an invalid name, please try again.\n";
        }
        break;    
    default:
        break;
    }
    return;
}

void Menu::AskDifficultyLevel() {
    std::string userName{""};
    switch(gameMode) {
    case 0:
        // Quit
        break;
    case 1:
        // Singleplayer
        while(isQuit != 1) {
            PrintAskDifficultyLevelLines(userName);
            std::cin >> difficultyLevelR;
            // If submitted difficulty level is valid, while loop is broken
            if(CheckDifficultyLevel(difficultyLevelR))
                break;
        }
        break;
    case 2:
        // Multiplayer
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
        break;
    default:
        break;
    }
    return;
}

void Menu::PrintAskDifficultyLevelLines(std::string &userName) {
    switch (gameMode) {
    case 0:
        // Quit
        break;
    case 1:
        std::cout << "Please enter the difficulty level (e.g: 2):\n";
        // Singleplayer
        break;
    case 2:
        std::cout << "Please enter the difficulty level for " << userName << " (e.g: 2):\n";
        // Multiplayer
        break;
    default:
        break;
    }
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

void Menu::FinalScreenSingle(int scoreR) {
    std::cout << "Game Over!\n";
    // Singleplayer
    std::cout << "You made the score of " << scoreR << ".\n";
    if(scoreR > highestScore)
        std::cout << "You made a new record!\n";
    else if(scoreR > lastHighestScoreR)
        std::cout << "You made your highest score!\n";
    DisplayGameDuration();
    return;
}

void Menu::FinalScreenMulti(int winner, int scoreR, int scoreL) {
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
    DisplayGameDuration();
    return;
}

void Menu::DisplayGameDuration() {
    gameDuration *= 100;
    gameDuration = static_cast<int>(gameDuration);
    gameDuration /= 100.0;
    std::cout << "Game duration was " << gameDuration << " seconds.\n";
    // A line with stars is used to separate new and previous game screens
    std::cout << "********************************\n";
    return;
}