// Ex4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using std::cin;
using std::cout;

// Напишете програма, която чете три цели числа от стандартния вход. 
//Напишете функция, която приема трите числа и име на файл, в който ще запишете сумата и произведението им.

void saveSumAndMultiplicationOfThreeNumbers(int a, int b, int c, const char* fileName)
{
    if (!fileName)
    {
        return;
    }

    std::ofstream ofs(fileName);

    if (!ofs.is_open())
    {
        return;
    }

    ofs << "Sum of a, b, c: " << a + b + c << std::endl;
    ofs << "Multiplication of a, b, c: " << a * b * c;

    ofs.close();
}

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    saveSumAndMultiplicationOfThreeNumbers(a, b, c, "ex4.txt");
}
