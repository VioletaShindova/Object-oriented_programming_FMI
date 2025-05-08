#include "Interval.h"
#include <iostream>
#include <cmath>

void sieve(bool* sieve, size_t len) {
	for (size_t i = 2; i * i <= len; ++i) {
		if (!sieve[i]) {
			for (size_t j = i * i; j < len; j += i)
				sieve[j] = true;
		}
	}
}

size_t countPrimesInInterval(const bool* sieve, int a, int b) {
	size_t count = 0;
	for (int i = std::max(2, a); i <= b; ++i) {
		if (!sieve[i])
			++count;
	}

	return count;
}

int reversedNumber(int number) {
	int result = 0;
	while (number != 0) {
		((result += (number % 10)) *= 10);
		number /= 10;
	}

	return result;
}

bool isPallindrome(int number) {
	return number == reversedNumber(number);
}

bool hasDifferentDigits(int number) {
	unsigned counter = 0;
	unsigned tempIndex = 0;
	int tempNumber = number;

	while (number != 0) {
		if (counter > 1)
			return false;

		if (number % 10 == tempIndex)
			counter++;

		if (tempIndex < 10 && (number / 10) == 0) {
			number = tempNumber;
			tempIndex++;
		}
	}

	return true;
}

bool isPowerOfTwo(int number) {
	return number > 0 && (number & (number - 1)) == 0;
}

Interval::Interval(int a, int b) {
	setA(a, b);
	setB(a, b);
}

void Interval::setA(int a, int b) {
	if (!isLessThanEqualTo(a, b))
		throw std::invalid_argument("A is bigger than B");

	this->a = a;
}

void Interval::setB(int a, int b) {
	if (!isLessThanEqualTo(a, b))
		throw std::invalid_argument("A is bigger than B");

	this->b = b;
}

const int& Interval::getA() const {
	return this->a;
}

const int& Interval::getB() const {
	return this->b;
}

const size_t& Interval::getSizeOfInterval() const {
	return (abs(this->b) - abs(this->a));
}

bool Interval::isNumberInRange(int number) const {
	return (this->a <= number) && (number <= this->b);
}

size_t Interval::calcPrimeNumbersInTheInterval() const {

	if (this->b < 2)
		return 0;

	size_t sieveSize = (this->b + 1);
	bool* sieveArr = new bool[sieveSize] {false};

	sieveArr[0] = true;
	sieveArr[1] = true;

	sieve(sieveArr, sieveSize);

	size_t count = countPrimesInInterval(sieveArr, a, b);

	delete[] sieveArr;
	return count;
}

size_t Interval::getNumberOfPrimePallindromNumbers() const {
	if (this->b < 2)
		return 0;

	size_t sieveSize = (this->b + 1);
	bool* sieveArr = new bool[sieveSize] {false};

	sieveArr[0] = true;
	sieveArr[1] = true;

	sieve(sieveArr, sieveSize);

	size_t primePalindromsCounter = 0;

	for (int i = std::max(2, a); i <= b; ++i) {
		if (!sieveArr[i] && isPallindrome(i))
			++primePalindromsCounter;
	}

	delete[] sieveArr;
	return primePalindromsCounter;
}

size_t Interval::countOfNumberWithDifferentDigits() const {
	size_t countOfNumbersWithDiffDigits = 0;

	for (size_t i = this->a; i <= this->b; i++) {
		if (hasDifferentDigits(i))
			++countOfNumbersWithDiffDigits;
	}

	return countOfNumbersWithDiffDigits;
}

bool Interval::areBothEndsPowersOfTwo() const {
	return isPowerOfTwo(this->a) && isPowerOfTwo(this->b);
}

const Interval& Interval::intersect(const Interval& other) const {
	return { std::max(other.a,this->a), std::min(other.b, this->b) };
}

bool Interval::isSuperInterval(const Interval& other) const {
	if (other.a > other.b)
		return false;

	return (this->a <= other.a) && (other.b <= this->b);
}

bool Interval::isLessThanEqualTo(int a, int b) const {
	return a <= b;
}