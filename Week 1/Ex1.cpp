// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

/*
1. Напишете функция, която приема символен низ и връща ново заделен символен низ, съдържащ само цифрите от подадения низ.
Пример:
Вход:

)Lso!c6d%9ucpB*CED5su2DH%&7t4)*
Изход:

695274
*/

bool checkIfDigit(char symbol)
{
    return ('0' <= symbol && symbol <= '9');
}

unsigned countDigits(const char* arr)
{
    if (!arr)
    {
        return 0;
    }
    unsigned counter = 0;
    while (*arr)
    {
        if (checkIfDigit(*arr))
        {
            counter++;
        }
        arr++;
    }
    return counter;
}

char* separateNumbers(char* arr)
{
    if (!arr)
    {
        return nullptr;
    }

    unsigned numberOfDigits = countDigits(arr);
    char* newArr = new char[numberOfDigits + 1]; 
    char* temp = newArr;
    while (*arr)
    {
        if (checkIfDigit(*arr))
        {
            *temp = *arr;
            temp++;
        }
        arr++;
    }
    *temp = 0;
    return newArr;
}

int main()
{
    char arr[] = ")c6d%9uD5u2%&74*";
   
    char* ptr = separateNumbers(arr);
    
    std::cout << ptr;

    delete[] ptr;
}

