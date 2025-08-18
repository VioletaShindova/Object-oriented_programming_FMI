#include "Point.h"

Point::Point() : Point(0, 0) {}

Point::Point(int x, int y)
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
		throw std::invalid_argument("Stream is not good\n");

	return os << "X:" << other.x << "Y:" << other.y;
}

bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.getX() == rhs.getX() &&
		lhs.getY() == rhs.getY();
}

bool operator!=(const Point& lhs, const Point& rhs)
{
	return !(lhs == rhs);
}
