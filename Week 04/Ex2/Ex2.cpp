// Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;

#define MIN(a,b) (a < b) ? a : b

/*
Напревете следните функционалности:

записване на масив от цели числа в двоичен файл

прочитане на двоичен файл с цели числа и да се съхрани в подходящ масив

извличане n-то число от двоичен файл, като двоичния файл не се зарежда в паметта (гарантирано е, че n < броя на числата)

Упътване: целите числа са от тип int
*/

constexpr size_t ARR_SIZE = 7;

bool writeArrOfIntsInFile(const char* fileName, int arr[ARR_SIZE])
{
    if (!fileName)
        return false;

    std::ofstream ofs(fileName, std::ios::binary);

    if (!ofs.is_open())
        return false;

    ofs.write((const char*)arr, sizeof(int) * ARR_SIZE);

    ofs.close();

    return true;
}

int getFileSize(std::ifstream& ifs)
{
    int curr = ifs.tellg();
    ifs.seekg(0, std::ios::end);

    size_t result = ifs.tellg();

    ifs.seekg(curr, std::ios::beg);

    return result;
}

bool readArrOfIntsInFile(const char* fileName, int arr[])
{
    if (!fileName)
        return false;

    std::ifstream ifs(fileName, std::ios::binary);

    if (!ifs.is_open())
        return false;

    ifs.read((char*)arr, MIN(getFileSize(ifs), (int)ARR_SIZE));

    ifs.close();

    return true;
}

int main()
{
    int arr[] = { 1,2,3,4,5,6,15 };
    
    if (!writeArrOfIntsInFile("ex2_fileWithIntegers.txt", arr))
        std::cerr << "Invalid file name";

    int newArr[ARR_SIZE]{0};
    if(!readArrOfIntsInFile("ex2_fileWithIntegers.txt", newArr))
        std::cerr << "Invalid file name";

    int nNumber = 0;
    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        cout << newArr[i] << ' ';
        if (i == nNumber)
            nNumber = newArr[i];
    }
    
    cout << nNumber;
}


