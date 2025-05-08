// Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Създайте структура, която представлява точка в двумерното пространство. Също така, реализирайте следните функции:

четене от стандартния вход
принтиране на стандартния изход
разстояние между две точки
*/

#include <iostream>
#include "Point.h"

int main()
{
    Point p1;

    Point p2;

    readInputOfCoordinates(p1);

    printOutput(p1);

    readInputOfCoordinates(p2);

    printOutput(p2);

    std::cout << "The length between p1 and p2 is: " << getLengthBetweenTwoPoints(p1, p2);
}

