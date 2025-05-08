// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

/*
Напишете функция, която приема име на текстов файл и принтира на стандартния изход съдържанието му.
*/

//size_t currIndex = ifs.tellg() - returns the current position of the get*
//ifs.clear() // bad fail eof
//ifs.seekg(currIndex); //gets pointer back in the beginning

//23456|8324|56743
//RGB = R * 256 * 256 + G * 256 + B
//ifs.ignore() - skips current position
///ifs.get() - combination of ifs.peek() && ifs.ignore()
//get* e член-данна, което означава, че променяме състоянието на файла, заради това потоците не можем
//да ги подаваме по константни референции

//ofs << " /b " - rewrites the last 2 positions

void readColor(std::ifstream& ifs)
{
    unsigned rgb; 
    ifs >> rgb; //read until ifs meets white space (by default)
}

void printContentsFromFile(char text[])
{
    std::ifstream ifs(text);


}

void printContentOfFile(char fileName[20])
{
    std::ifstream ifs(fileName);

    if (!ifs.is_open())
    {
        throw "File can't be opened!";
        return;
    }

    char buffer[1024];
    unsigned index = 0;
    while (!ifs.eof() && !ifs.bad())
    {
        buffer[index] = ifs.get();
        index++;
    }
    buffer[index] = '\0';
    cout << buffer;
    ifs.close();
}

int main()
{
    char text[20] = "";

    cin >> text;

    printContentOfFile(text);


}
