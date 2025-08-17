#include "Point.h"

Point::Point() : x(0), y(0) {}

Point::Point(int x, int y) : x(0), y(0)
{
	setX(x);
	setY(y);
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

std::ostream& operator<<(std::ostream& os, const Point& other)
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	return os << "X: " << other.x
		<< ", Y:" << other.y << '\n';
}
