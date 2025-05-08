// Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

//Напишете функция, която приема имена на два текстов файла и копира съдържанието на първия файл във втория.

void copy(std::ofstream& ofsCopyTo, std::ifstream& ifsCopyFrom)
{
    int current = ifsCopyFrom.tellg();
    char buffer[1024]{};

    unsigned index = 0;
    char currentSymbol;
    while (ifsCopyFrom.get(currentSymbol))
    {
        buffer[index] = currentSymbol;
        index++;
    }

    ofsCopyTo << buffer;

    ifsCopyFrom.seekg(current);

}

void copyContents(const char* fileCopyTo, const char* fileCopyFrom)
{
    if (!fileCopyTo)
    {
        return;
    }

    if (!fileCopyFrom)
    {
        return;
    }

    std::ifstream ifsCopyFrom(fileCopyFrom);
    std::ofstream ofsCopyTo(fileCopyTo);

    if (!ifsCopyFrom.is_open())
    {
        return;
    }

    if (!ofsCopyTo.is_open())
    {
        return;
    }

    copy(ofsCopyTo, ifsCopyFrom);

    ofsCopyTo.close();
    ifsCopyFrom.close();

}

int main()
{
    copyContents("FileCopyTo.txt", "FileCopyFrom.txt");
}
