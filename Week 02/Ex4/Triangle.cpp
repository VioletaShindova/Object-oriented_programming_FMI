#include <iostream>
#include "Triangle.h"

/*
Създайте структура, която представлява фигурата триъгълник. Също така, реализирайте следните функции:

четене от стандартния вход
принтиране на стандартния изход
пресмятане на обиколка
пресмятане на лице
връщане на типа на триъгълника спрямо страните му(равнобедрен, равностранен, разностранен)
връщане на типа на триъгълника спрямо ъглите му(остроъгълен, правоъгълен, тъпоъгълен)
*/

void readPoint(Point& point)
{
	std::cout << "Input x: ";
	std::cin >> point.x;

	std::cout << "Input y: ";
	std::cin >> point.y;
}

void readTrianlge(Triangle& tr)
{
	std::cout << "Input coordinates of A: ";
	readPoint(tr.A);

	std::cout << "Input coordinates of B: ";
	readPoint(tr.B);

	std::cout << "Input coordinates of C: ";
	readPoint(tr.C);
}

void printPoint(const Point& point)
{
	std::cout << "x = " << point.x;
	std::cout << ", y = " << point.y << ')' << std::endl;
}

void printTriangle(const Triangle& tr)
{
	std::cout << "A(";
	printPoint(tr.A);

	std::cout << "B(";
	printPoint(tr.B);

	std::cout << "C(";
	printPoint(tr.C);
}

double getLengthBetweenTwoPoints(const Point& p1, const Point& p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double getPerimeter(const Triangle& tr)
{
	double AB = getLengthBetweenTwoPoints(tr.A, tr.B);
	double BC = getLengthBetweenTwoPoints(tr.B, tr.C);
	double CA = getLengthBetweenTwoPoints(tr.C, tr.A);

	return AB + BC + CA;
}

//heron
double getArea(const Triangle& tr)
{
	double getHalfPerimeter = getPerimeter(tr) / 2;

	double AB = getLengthBetweenTwoPoints(tr.A, tr.B);
	double BC = getLengthBetweenTwoPoints(tr.B, tr.C);
	double CA = getLengthBetweenTwoPoints(tr.C, tr.A);

	return sqrt(getHalfPerimeter * (getHalfPerimeter - AB) * (getHalfPerimeter - BC) * (getHalfPerimeter - CA));
}

TypeTriangleBySidesLength getTypeOfTriangleBySidesLengths(const Triangle& tr)
{
	double AB = getLengthBetweenTwoPoints(tr.A, tr.B);
	double BC = getLengthBetweenTwoPoints(tr.B, tr.C);
	double CA = getLengthBetweenTwoPoints(tr.C, tr.A);

	if (AB == BC)
	{
		if (BC == CA)
		{
			return TypeTriangleBySidesLength::EQUILATERAL;
		}
		else
		{
			return TypeTriangleBySidesLength::ISOSCELES;
		}
	}
	else if (BC == CA)
	{
		if (CA == AB)
		{
			return TypeTriangleBySidesLength::EQUILATERAL;
		}
		else
		{
			return TypeTriangleBySidesLength::ISOSCELES;
		}
	}
	else
	{
		return TypeTriangleBySidesLength::SCALENE;
	}
}
 
double pythagorasTheorem(double oneSide, double otherSide)
{
	return (oneSide * oneSide) + (otherSide * otherSide);
}

double* selectionSort(double AB, double BC, double CA) 
{
	size_t tempSize = 3;

	double* temp = new double[tempSize];
	temp[0] = AB;
	temp[1] = BC;
	temp[2] = CA;

	for (size_t i = 0; i < tempSize - 1; i++)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; j < tempSize; j++)
		{
			if (temp[j] < temp[minIndex])
			{
				minIndex = j;
			}
		}

		if (minIndex != i)
		{
			std::swap(temp[i], temp[minIndex]);
		}
	}

	return temp;
}

//angle
TypeTriangleByAngle getTypeOfTriangleByAngle(const Triangle& tr)
{
	double AB = getLengthBetweenTwoPoints(tr.A, tr.B);
	double BC = getLengthBetweenTwoPoints(tr.B, tr.C);
	double CA = getLengthBetweenTwoPoints(tr.C, tr.A);

	double* temp = selectionSort(AB, BC, CA);

	if (temp[2] < sqrt(pythagorasTheorem(temp[0], temp[1])))
	{
		delete[] temp;
		return TypeTriangleByAngle::ACUTE;
	}
	else if (temp[2] > sqrt(pythagorasTheorem(temp[0], temp[1])))
	{
		delete[] temp;
		return TypeTriangleByAngle::OBTUSE;
	}
	else
	{
		delete[] temp;
		return TypeTriangleByAngle::RIGHT;
	}
}