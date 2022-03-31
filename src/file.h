#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class File {
    public:
        void CheckFile(std::string &newUserName, int &lastHighestScore, int &highestScore);
        void OpenFile();
        void ReadFileData(std::string &newUserName, int &lastHighestScore, int &highestScore);
        void AddData(std::string &userName, int score);
        void CloseFile();
    private:
        std::fstream dataFile;
        std::fstream dataFileAppend;
};

#endif