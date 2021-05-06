#include <string>
#include <fstream>
#include <iostream>

#ifndef BINFILEHANDLER_H
#define BINFILEHANDLER_H


class BinFileHandler
{
public:
    inline BinFileHandler() {};

    template<typename T>
    inline T* readFromFile(std::string filePath)
    {
        T* result = nullptr;

        std::ifstream configFile{filePath, std::ios::out | std::ios::binary};

        if(configFile)
        {
            result = new T;
            configFile.read(reinterpret_cast<char *>(result), sizeof(T));
            configFile.close();
        }

        return result;
    }

    template<typename T>
    inline void saveToFile(std::string filePath, T &data)
    {
        std::ofstream configFile{filePath, std::ios::out | std::ios::binary | std::ios::trunc};

        if(configFile)
        {
            configFile.write(reinterpret_cast<char *>(&data), sizeof(T));
            configFile.close();
        }
    }
};

#endif // BINFILEHANDLER_H
