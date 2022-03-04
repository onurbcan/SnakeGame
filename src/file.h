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
        void AddData(std::string newUserName, int &lastScore);
        void CloseFile();
    private:
        std::fstream dataFile;
};

#endif