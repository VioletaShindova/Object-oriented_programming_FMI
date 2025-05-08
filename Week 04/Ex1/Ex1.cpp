// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;

//Напишете програма, която приема файл и показва каква е големината му.

size_t getLengthOfFile(const char* fileName)
{
    if (!fileName)
        return 0;

    std::ifstream ifs(fileName);
    if (!ifs.is_open())
        return 0;

    size_t counter = 0;
    while (!ifs.eof())
    {
        ifs.get();
        counter++;
    }

    ifs.close();
    return counter;
}

int main()
{
    try {
        cout << getLengthOfFile("ex1_file.txt");

    }
    catch (std::bad_alloc& ba) {
     
    }
}

