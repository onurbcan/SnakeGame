#include "file.h"

void File::CheckFile(std::string &newUserNameR, std::string &newUserNameL, 
                        int &lastHighestScoreR, int &lastHighestScoreL,
                        int &highestScore) {
    dataFile.open("GameData.txt");
    if(dataFile) {
        // File exists, read data inside
        ReadFileData(newUserNameR, lastHighestScoreR, highestScore);
        ReadFileData(newUserNameL, lastHighestScoreL, highestScore);
        CloseFile();
    } else {
        // No file exists, create a new one
        OpenFile();
        CloseFile();
    }
}

void File::OpenFile() {
    dataFile.open("GameData.txt");
}

void File::ReadFileData(std::string &newUserName, int &lastHighestScore, int &highestScore) {
    std::string userName;
    int score;
    // Data in the file checked using user name and relevant scores are saved if available
    while(dataFile >> userName >> score) {
        if(newUserName.compare(userName) == 0)
            if(score > lastHighestScore)
                lastHighestScore = score;
        if(score > highestScore)
            highestScore = score;
        userName.clear();
    }
}

void File::AddData(std::string &userNameR, std::string &userNameL, int scoreR, int scoreL) {
    dataFileAppend.open("GameData.txt", std::ios::app);
    dataFileAppend << userNameR << " " << scoreR << "\n";
    dataFileAppend << userNameL << " " << scoreL << "\n";
    CloseFile();
}

void File::CloseFile() {
    dataFile.close();
}