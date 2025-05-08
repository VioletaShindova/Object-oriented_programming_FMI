#pragma once

void sieve(bool* sieve, size_t len);

size_t countPrimesInInterval(const bool* sieve, int a, int b);

int reversedNumber(int number);

bool isPallindrome(int number);

bool hasDifferentDigits(int number);

bool isPowerOfTwo(int number);

class Interval
{
public:
	Interval() = default;

	Interval(int a, int b);

	void setA(int a, int b);

	void setB(int a, int b);

	const int& getA() const;

	const int& getB() const;

	const size_t& getSizeOfInterval() const;

	bool isNumberInRange(int number) const;

	size_t calcPrimeNumbersInTheInterval() const;

	size_t getNumberOfPrimePallindromNumbers() const;

	size_t countOfNumberWithDifferentDigits() const;

	bool areBothEndsPowersOfTwo() const;

	const Interval& intersect(const Interval& other) const;

	bool isSuperInterval(const Interval& other) const;
	
private:
	bool isLessThanEqualTo(int a, int b) const;

	int a = 0;
	int b = 0;
};