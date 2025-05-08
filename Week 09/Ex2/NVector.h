#pragma once
#include <iostream>


class NVector
{
public:
	NVector();

	NVector(int a, int b);

	void setA(int a);

	void setB(int b);

	int getAConst() const;

	int getBConst() const;

	int getA();

	int getB();

	double getLengthOfVector() const;

	NVector& operator+=(const NVector& rhs);

	NVector& operator-=(const NVector& rhs);

	NVector& operator*=(int scalar);

	friend bool areParallel(const NVector& lhs, const NVector& rhs);

	friend bool arePerpendicular(const NVector& lhs, const NVector& rhs);

	friend std::ostream& operator<<(std::ostream& os, const NVector& rhs);

	friend std::istream& operator>>(std::istream& is, NVector& rhs);

private:
	int a;
	int b;
};

NVector operator+(const NVector& lhs, const NVector& rhs);

NVector operator-(const NVector& lhs, const NVector& rhs);

NVector operator*(const NVector& lhs, int scalar);

NVector operator*(int scalar, const NVector& rhs);

NVector operator-(const NVector& rhs);