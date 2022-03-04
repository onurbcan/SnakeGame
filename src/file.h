#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class File {
    public:
        void CheckFile(std::string newUserName, int &lastScore);
        void OpenFile();
        void ReadFileData(std::string newUserName, int &lastScore);
        void GetHighestScore(std::string newUserName, int &lastHighestScore);
        void AddData(std::string UserName, int score);
        void CloseFile();
    private:
        std::fstream dataFile;
        std::fstream dataFileAppend;
};

#endif