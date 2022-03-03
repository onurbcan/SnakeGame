#include "file.h"

void File::CheckFile() {
    dataFile.open("GameData.txt");
    if(dataFile) {
        std::cout << "file exists\n";
    } else {
        OpenFile();
    }
}

void File::OpenFile() {
    dataFile.open("GameData.txt");
    dataFile << "Writing this to a file.\n";
    dataFile.close();
}

bool CheckWord(char* str)
{
    //std::string filename("input.txt");
    std::vector<std::string> words;
    std::string word;
    /*
    if (!dataFile.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }
    */
    while( dataFile >> word) {
        words.push_back(word);
    }
    
    for (const auto &i : words) {
        std::cout << i << std::endl;
    }

}

/*
void File::AddData() {
    
}

void File::CloseFile() {
    
}
*/