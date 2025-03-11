#pragma once
#include <iostream>

enum class PowOfI {
	INVALID,
	FIRST,	     //i
	SECOND,		 //-1
	THIRD,	     //-i
	FOURTH		 //1
};

struct ComplexNumber {
	int a = 0;
	int b = 0;
	PowOfI powerOfI = PowOfI::INVALID;
};

ComplexNumber obtainingComplexNumber(ComplexNumber& complexNumber);

ComplexNumber sumOfTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2);

ComplexNumber subtractionOfTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2);

int getSumOfPowerOfTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2);

ComplexNumber multiplyTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2, int sumOfPowers);

void divideTwoComplexNumbers(const ComplexNumber& complexNumberZ1, const ComplexNumber& complexNumberZ2);

bool areEqual(const ComplexNumber& firstNumber, const ComplexNumber& secondNumber);

void printComplexNumber(const ComplexNumber& complexNumber);