#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class File {
    public:
        void CheckFile();
        void OpenFile();
        //void AddData();
        //void CloseFile();
    private:
        std::fstream dataFile;
        std::string userName{"user1"};
};

#endif