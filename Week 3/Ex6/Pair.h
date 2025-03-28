#pragma once
#include <exception>

struct Pair {
public:
	Pair() = default;

	Pair(unsigned firstNumber, unsigned secondNumber);

	bool setFirstNumber(unsigned firstNumber);

	bool setSecondNumber(unsigned secondNumber);

	unsigned getFirstNumber() const;

	unsigned getSecondNumber() const;

private:
	bool isValidNumber(unsigned number) const;

	unsigned firstNumber = 0;
	unsigned secondNumber = 0;
};