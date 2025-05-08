#include "Pair.h"

Pair::Pair(unsigned firstNumber, unsigned secondNumber)
{
	(void)setFirstNumber(firstNumber);

	(void)setSecondNumber(secondNumber);
}

bool Pair::setFirstNumber(unsigned firstNumber)
{
	if (!isValidNumber(firstNumber))
	{
		throw std::exception("The number is our of range!");
	}

	this->firstNumber = firstNumber;
	return true;
}

bool Pair::setSecondNumber(unsigned secondNumber)
{
	if (!isValidNumber(secondNumber))
	{
		throw std::exception("The number is our of range!");
	}

	this->secondNumber = secondNumber;
	return true;
}

unsigned Pair::getFirstNumber() const
{
	return this->firstNumber;
}

unsigned Pair::getSecondNumber() const
{
	return this->secondNumber;
}

bool Pair::isValidNumber(unsigned number) const
{
	return 0 <= number;
}