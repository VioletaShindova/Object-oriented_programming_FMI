#include "ComplexNumber.h"

ComplexNumber::ComplexNumber() : real(0), im(0) {}

ComplexNumber::ComplexNumber(double real, double im) : real(real), im(im) {}

void ComplexNumber::setIm(double im) {
	this->im = im;
}

void ComplexNumber::setReal(double real) {
	this->real = real;
}

double ComplexNumber::getImConst() const {
	return im;
}

double ComplexNumber::getRealConst() const {
	return real;
}

double ComplexNumber::getIm() {
	return im;
}

double ComplexNumber::getReal() {
	return real;
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other) {
	real += other.real;
	im += other.im;

	return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& other) {
	real -= other.real;
	im -= other.im;

	return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& other) {
	double oldReal = real;
	real = (real * other.real) - (im * other.im);
	im *= (oldReal * other.im) + (im * other.real);

	return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& other) {
	real = (real * other.real) + (im * other.im) / (other.real * other.real) + (other.im * other.im);
	im = (other.real * im) - (real * other.im) / (other.real * other.real) + (other.im * other.im);

	return *this;
}

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	ComplexNumber temp(lhs);
	temp += rhs;
	return temp;
}

ComplexNumber operator+(const ComplexNumber& lhs, double rhs) {
	ComplexNumber temp(lhs);
	temp.setIm(temp.getIm() + rhs);
	return temp;
}
ComplexNumber operator+(double lhs, const ComplexNumber& rhs) {
	ComplexNumber temp(rhs);
	temp.setIm(temp.getIm() + lhs);
	return temp;
}

ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	ComplexNumber temp(lhs);
	temp -= rhs;
	return temp;
}

ComplexNumber operator-(const ComplexNumber& lhs, double rhs) {
	ComplexNumber temp(lhs);
	temp.setIm(temp.getIm() - rhs);
	return temp;
}
ComplexNumber operator-(double lhs, const ComplexNumber& rhs) {
	ComplexNumber temp(rhs);
	temp.setIm(temp.getIm() - lhs);
	return temp;
}

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	ComplexNumber temp(lhs);
	temp *= rhs;
	return temp;
}

ComplexNumber operator*(const ComplexNumber& lhs, double rhs) {
	ComplexNumber temp(lhs);
	temp.setIm(temp.getIm() * rhs);
	return temp;
}
ComplexNumber operator*(double lhs, const ComplexNumber& rhs) {
	ComplexNumber temp(rhs);
	temp.setIm(temp.getIm() * lhs);
	temp.setReal(temp.getReal() * lhs);
	return temp;
}

ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	ComplexNumber temp(lhs);
	temp /= rhs;
	return temp;
}

ComplexNumber operator/(const ComplexNumber& lhs, double rhs) {
	ComplexNumber temp(lhs);
	temp.setIm(temp.getIm() / rhs);
	temp.setReal(temp.getReal() / rhs);
	return temp;
}
ComplexNumber operator/(double lhs, const ComplexNumber& rhs) {
	ComplexNumber temp(rhs);
	temp.setIm(temp.getIm() / lhs);
	temp.setReal(temp.getReal() / lhs);
	return temp;
}

bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	return (lhs.real == rhs.real) && (lhs.im == rhs.im);
}

bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& lhs) {
	os << "Real: " << lhs.real << " Im:" << lhs.im << std::endl;

	return os;
}

std::istream& operator>>(std::istream& is, ComplexNumber& lhs) {
	is >> lhs.real >> lhs.im;

	return is;
}

bool operator<(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	return lhs.real < rhs.real || (lhs.real == rhs.real && lhs.im < rhs.im);
}

bool operator>(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	return !(lhs < rhs) && (lhs != rhs);
}

ComplexNumber operator-(const ComplexNumber& rhs) {
	ComplexNumber temp(rhs);
	temp.setIm(rhs.getImConst() * (-1));
	return temp;
}

//void operator-(ComplexNumber& rhs) {
//	rhs.setIm(rhs.getImConst() * (-1));
//}