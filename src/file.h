#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class File {
    public:
        void CheckFile(std::string &newUserNameR, std::string &newUserNameL, 
                        int &lastHighestScoreR, int &lastHighestScoreL, int &highestScore);
        void AddDataSingle(std::string &userNameR, int scoreR);
        void AddDataMulti(std::string &userNameR, std::string &userNameL, int scoreR, int scoreL);
    private:
        void OpenFile();
        void ReadFileData(std::string &newUserName, int &lastHighestScore, int &highestScore);
        void CloseFile();
        std::fstream dataFile;
        std::fstream dataFileAppend;
};

#endif