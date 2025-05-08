// Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ComplexNumber.h"

using std::cout;
using std::cin;
using std::endl;
/*
Създайте структура, която представлява комплексно число. Също така, реализирайте следните функции:

получаване на комплексно спрегнатото на комплексно число
събиране на 2 комплексни числа
изваждане на 2 комплексни числа
умножение на 2 комплексни числа
деление на 2 комплексни числа
сравнение за равенство на 2 комплексни числа
принтиране на комплексно число
*/

int main()
{
    ComplexNumber z1 = { 3, 4, PowOfI::FIRST };
    cout << "z1 = " << z1.a << "+" << z1.b << "i" << endl;
    ComplexNumber z2 = { -2, 5, PowOfI::FIRST };
    cout << "z2 = " << z2.a << "+" << z2.b << "i" << endl;

    ComplexNumber sumOfTwoNumbers = sumOfTwoComplexNumbers(z1, z2);
    ComplexNumber subOfTwoNumbers = subtractionOfTwoComplexNumbers(z1, z2);
    ComplexNumber multiplyTwoNumbers = multiplyTwoComplexNumbers(z1, z2, getSumOfPowerOfTwoComplexNumbers(z1, z2));
    cout << "Division: ";  
    divideTwoComplexNumbers(z1, z2);
    //ComplexNumber divideTwoNumbers = divideTwoComplexNumbers(z1, z2);
    cout << endl;

    cout << (areEqual(z1, z2) ? ("z1 is equal to z2") : ("z1 is NOT equal to z2")) << endl;

    cout << "Sum: " << sumOfTwoNumbers.a << ", " << sumOfTwoNumbers.b << endl;
    cout << "Subtraction: " << subOfTwoNumbers.a << ", " << subOfTwoNumbers.b << endl;
    cout << "Multiplication: " << multiplyTwoNumbers.a << ", " << multiplyTwoNumbers.b << endl;
    //cout << "Division: " << divideTwoNumbers.a << divideTwoNumbers.b << endl;
}
