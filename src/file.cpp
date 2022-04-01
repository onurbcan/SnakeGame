#include "file.h"

void File::CheckFile(std::string &newUserName, int &lastHighestScore, int &highestScore) {
    dataFile.open("GameData.txt");
    if(dataFile) {
        // file exists, read data inside
        ReadFileData(newUserName, lastHighestScore, highestScore);
        CloseFile();
    } else {
        // no file exists, create a new one
        OpenFile();
        CloseFile();
    }
}

void File::OpenFile() {
    dataFile.open("GameData.txt");
    //dataFile << "Writing this to a file.\n";
}

void File::ReadFileData(std::string &newUserName, int &lastHighestScore, int &highestScore) {
    std::string userName;
    int score;
    while(dataFile >> userName >> score) {
        if(newUserName.compare(userName) == 0)
            if(score > lastHighestScore)
                lastHighestScore = score;
        if(score > highestScore)
            highestScore = score;
        userName.clear();
    }
}

void File::AddData(std::string &userName, int score) {
    dataFileAppend.open("GameData.txt", std::ios::app);
    dataFileAppend << userName << " " << score << std::endl;
}

void File::CloseFile() {
    dataFile.close();
}