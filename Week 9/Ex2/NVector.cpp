#include "NVector.h"

NVector::NVector() : NVector(0, 0) {}

NVector::NVector(int a, int b) : a(a), b(b) {}

void NVector::setA(int a) {
	this->a = a;
}

void NVector::setB(int b) {
	this->b = b;
}

int NVector::getAConst() const {
	return a;
}

int NVector::getBConst() const {
	return b;
}

int NVector::getA() {
	return a;
}

int NVector::getB() {
	return b;
}

double NVector::getLengthOfVector() const {
	return sqrt(a * a + b * b);
}

NVector& NVector::operator+=(const NVector& rhs) {
	a += rhs.a;
	b += rhs.b;

	return *this;
}

NVector& NVector::operator-=(const NVector& rhs) {
	a -= rhs.a;
	b -= rhs.b;

	return *this;
}

NVector& NVector::operator*=(int scalar) {
	a *= scalar;
	b *= scalar;

	return *this;
}

bool areParallel(const NVector& lhs, const NVector& rhs) {
	return (lhs.a / rhs.a) == (lhs.b / rhs.b);
}

bool arePerpendicular(const NVector& lhs, const NVector& rhs) {
	return ((lhs.a * rhs.a) + (lhs.b * rhs.b)) == 0;
}

std::ostream& operator<<(std::ostream& os, const NVector& rhs) {
	os << "A: " << rhs.a << " B: " << rhs.b << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, NVector& rhs) {
	is >> rhs.a >> rhs.b;
	return is;
}

NVector operator+(const NVector& lhs, const NVector& rhs) {
	NVector temp(lhs);
	temp += rhs;
	return temp;
}

NVector operator-(const NVector& lhs, const NVector& rhs) {
	NVector temp(lhs);
	temp -= rhs;
	return temp;
}

NVector operator*(const NVector& lhs, int scalar) {
	NVector temp(lhs);
	temp *= scalar;
	return temp;
}

NVector operator*(int scalar, const NVector& rhs) {
	NVector temp(rhs);
	temp *= scalar;
	return temp;
}

NVector operator-(const NVector& rhs) {
	NVector temp(rhs);
	temp.setA(rhs.getBConst());
	temp.setB(rhs.getAConst());

	return temp;
}