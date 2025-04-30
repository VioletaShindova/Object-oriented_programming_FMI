#pragma once
#include <iostream>

class ComplexNumber
{
public:
	ComplexNumber();

	ComplexNumber(double real = 0, double im = 0);

	void setIm(double im);

	void setReal(double real);

	double getRealConst() const;

	double getImConst() const;

	double getReal();

	double getIm();

	ComplexNumber& operator+=(const ComplexNumber& other);

	ComplexNumber& operator-=(const ComplexNumber& other);

	ComplexNumber& operator*=(const ComplexNumber& other);

	ComplexNumber& operator/=(const ComplexNumber& other);

	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& lhs);

	friend std::istream& operator>>(std::istream& is, ComplexNumber& lhs);

	friend bool operator<(const ComplexNumber& lhs, const ComplexNumber& rhs);

	friend bool operator>(const ComplexNumber& lhs, const ComplexNumber& rhs);

	friend bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs);

	friend bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs);

private:
	double real;
	double im;
};

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator+(const ComplexNumber& lhs, double rhs);
ComplexNumber operator+(double lhs, const ComplexNumber& rhs);

ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator-(const ComplexNumber& lhs, double rhs);
ComplexNumber operator-(double lhs, const ComplexNumber& rhs);

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator*(const ComplexNumber& lhs, double rhs);
ComplexNumber operator*(double lhs, const ComplexNumber& rhs);

ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator/(const ComplexNumber& lhs, double rhs);
ComplexNumber operator/(double lhs, const ComplexNumber& rhs);

ComplexNumber operator-(const ComplexNumber& rhs);
//void operator-(ComplexNumber& rhs);