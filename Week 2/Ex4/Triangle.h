#pragma once

enum class TypeTriangleBySidesLength : uint8_t {
	EQUILATERAL, //равностранен
	ISOSCELES,	 //равнобедрен
	SCALENE		 //разностранен
};

enum class TypeTriangleByAngle : uint8_t {
	ACUTE,  //остроъгълен
	RIGHT,	//правоъгълен
	OBTUSE	//тъпоъгълен
};

struct Point
{
	int x = 0;
	int y = 0;
};

struct Triangle
{
	Point A = { 0, 0 };
	Point B = { 0, 0 };
	Point C = { 0, 0 };
};

void readPoint(Point& point);

void readTrianlge(Triangle& tr);

void printPoint(const Point& point);

void printTriangle(const Triangle& tr);

double getLengthBetweenTwoPoints(const Point& p1, const Point& p2);

double getPerimeter(const Triangle& tr);

double getArea(const Triangle& tr);

TypeTriangleBySidesLength getTypeOfTriangleBySidesLengths(const Triangle& tr);

TypeTriangleByAngle getTypeOfTriangleByAngle(const Triangle& tr);