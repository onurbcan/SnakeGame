#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

class File {
    public:
        void OpenFile();
        //void AddData();
        //void CloseFile();
    private:
        std::ofstream dataFile;
};

#endif