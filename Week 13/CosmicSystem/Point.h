#pragma once

#ifndef __POINT_HEADER_INCLUDED_

#define __POINT_HEADER_INCLUDED_

#include <iostream>

class Point
{
public:
	Point();
	Point(int x, int y);

	void setX(int x);
	void setY(int y);

	inline int getX() const noexcept { return x; }
	inline int getY() const noexcept { return y; }

	friend std::ostream& operator<<(std::ostream& os, const Point& other);

private:
	int x;
	int y;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);

#endif