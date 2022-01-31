#include "file.h"

void File::OpenFile() {
    dataFile.open("GameData.txt");
    dataFile << "Writing this to a file.\n";
    dataFile.close();
}
/*
void File::AddData() {
    
}

void File::CloseFile() {
    
}
*/