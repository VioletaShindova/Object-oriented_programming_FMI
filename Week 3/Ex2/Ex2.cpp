// Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using std::cin;
using std::cout;

//Напишете функция, която приема име на текстов файл и принтира броя на редовете в него.
constexpr size_t MAX_FILE_NAME = 20;


void printNumberOfNewLines(const char* fileName)
{
    if (!fileName)
    {
        return;
    }

    std::ifstream ifs(fileName);

    if (!ifs.is_open())
    {
        return;
    }

    unsigned counter = 0;
    char current;
    while (ifs.get(current))
    {
        if (current == '\n')
        {
            counter++;
        }   
    }
    ifs.close();

    cout << "Count of new lines: " << counter + 1;
}


int main()
{
    printNumberOfNewLines("ex2.txt");


}

