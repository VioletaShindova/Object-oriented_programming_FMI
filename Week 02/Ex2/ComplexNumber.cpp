#include "ComplexNumber.h"
#include <iostream>
using std::cout;
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

ComplexNumber obtainingComplexNumber(const ComplexNumber& complexNumber)
{
	return { complexNumber.a, -complexNumber.b };
}

ComplexNumber sumOfTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2)
{
	return { complexNumberZ1.a + complexNumberZ2.a, complexNumberZ1.b + complexNumberZ2.b };
}

ComplexNumber subtractionOfTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2)
{
	return { complexNumberZ1.a - complexNumberZ2.a, complexNumberZ1.b - complexNumberZ2.b };
}

int getSumOfPowerOfTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2)
{
	return (int)complexNumberZ1.powerOfI + (int)complexNumberZ2.powerOfI;
}

ComplexNumber multiplyTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2, int sumOfPowers)
{
	if (sumOfPowers > 4)
	{
		sumOfPowers %= 4;
	}

	ComplexNumber newComplNum = { 0,0,PowOfI::INVALID };
	switch (sumOfPowers)
	{
	case (int)PowOfI::SECOND:
		newComplNum = { (complexNumberZ1.a * complexNumberZ2.a) - (complexNumberZ1.b * complexNumberZ2.b), (complexNumberZ1.b * complexNumberZ2.a) + (complexNumberZ1.a * complexNumberZ2.b), PowOfI::SECOND };
		break;
	case (int)PowOfI::THIRD:
		newComplNum = { (complexNumberZ1.a * complexNumberZ2.a) - (complexNumberZ1.b * complexNumberZ2.b), (complexNumberZ1.b * complexNumberZ2.a) + (complexNumberZ1.a * complexNumberZ2.b), PowOfI::THIRD };
		break;
	case (int)PowOfI::FIRST:
		newComplNum = { (complexNumberZ1.a * complexNumberZ2.a) - (complexNumberZ1.b * complexNumberZ2.b), (complexNumberZ1.b * complexNumberZ2.a) + (complexNumberZ1.a * complexNumberZ2.b), PowOfI::FIRST };
		break;
	case (int)PowOfI::FOURTH:
		newComplNum = { (complexNumberZ1.a * complexNumberZ2.a), (complexNumberZ1.b * complexNumberZ2.b), PowOfI::FOURTH };
		break;
	default:
		break;
	}

	return newComplNum;
}

void divideTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2)
{
	ComplexNumber dividend = multiplyTwoComplexNumbers(complexNumberZ1, obtainingComplexNumber(complexNumberZ2), getSumOfPowerOfTwoComplexNumbers(complexNumberZ1, complexNumberZ2));
	ComplexNumber divider = multiplyTwoComplexNumbers(complexNumberZ2, obtainingComplexNumber(complexNumberZ2), getSumOfPowerOfTwoComplexNumbers(complexNumberZ1, complexNumberZ2));

	cout << '(' <<dividend.a << '/' << divider.a << ") + (" << dividend.b << '/' << divider.a << ")i";
	
	//return { dividend.a / divider.a, dividend.b / divider.a };
}

bool areEqual(const ComplexNumber& firstNumber, const ComplexNumber& secondNumber)
{
	return (firstNumber.a == secondNumber.a) && (firstNumber.b == secondNumber.b);
}

void printComplexNumber(const ComplexNumber& complexNumber)
{
	std::cout << "z = " << complexNumber.a << " + " << complexNumber.b << "i^" << (int)complexNumber.powerOfI;
}