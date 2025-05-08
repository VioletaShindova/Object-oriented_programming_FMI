// Ex5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using std::cin;
using std::cout;

//Напишете функция, която приема имената на два текстови файла, 
//в които са записани цели числа в сортиран вид. Числата са разделени с интервал. 
//Запишете в нов файл числата от двата дайла в сортиран вид. Числата отново да са разделени с интервал.

bool mergeSortedFiles(const char* fisrtFileName, const char* secondFileName, const char* resultFileName)
{
    if (!fisrtFileName || !secondFileName || !resultFileName)
        return false;

    std::ifstream ifs1(fisrtFileName);
    std::ifstream ifs2(secondFileName);

    std::ofstream ofs(resultFileName);

    if (!ifs1.is_open() || !ifs2.is_open() || !ofs.is_open())
        return false;
    
    int num1, num2;
    bool hasNums1 = bool(ifs1 >> num1);
    bool hasNums2 = bool(ifs2 >> num2);

    while (hasNums1 && hasNums2) { //both files aren't finished
        if(num1 < num2) {
            ofs << num1 << ' ';
            hasNums1 = bool(ifs1 >> num1);
        }
        else {
            ofs << num2 << ' ';
            hasNums2 = bool(ifs2 >> num2);
        }
    }

    while (hasNums1) { //second file is finished
        ofs << num1 << ' ';
        hasNums1 = bool(ifs1 >> num1);
    }

    while (hasNums2) { //first file is finished
        ofs << num2 << ' ';
        hasNums2 = bool(ifs2 >> num2);
    }

    return true;
}

int main()
{
    if (!mergeSortedFiles("ex5_FirstFile.txt", "ex5_SecondFile.txt", "ex5_NewFile.txt"))
    {
        std::cout << "Couldn't open the file!";
    }
}

