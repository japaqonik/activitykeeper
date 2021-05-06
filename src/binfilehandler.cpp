#include "binfilehandler.h"


BinFileHandler::BinFileHandler()
{

}

template<typename T>
T* BinFileHandler::readFromFile(std::string filePath)
{

}

template<typename T>
void BinFileHandler::saveToFile(std::string filePath, T &data)
{

}

template int* BinFileHandler::readFromFile<int>(std::string path);
template void BinFileHandler::saveToFile<int>(std::string path, int& data );
