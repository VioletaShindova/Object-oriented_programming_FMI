#pragma once
#include "Point.h"
#include <iostream>

/*
Създайте структура, която представлява точка в двумерното пространство. Също така, реализирайте следните функции:

четене от стандартния вход
принтиране на стандартния изход
разстояние между две точки
*/

void readInputOfCoordinates(Point& p)
{
	std::cout << "Input x: ";
	std::cin >> p.x;

	std::cout << "Input y: ";
	std::cin >> p.y;
}

void printOutput(const Point& p)
{
	std::cout << '(' << p.x;
	std::cout << ", " << p.y << ')';
}

double getLengthBetweenTwoPoints(const Point& p1, const Point& p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}