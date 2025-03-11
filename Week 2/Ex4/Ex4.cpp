// Ex4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Triangle.h"

/*
Създайте структура, която представлява фигурата триъгълник. Също така, реализирайте следните функции:

четене от стандартния вход
принтиране на стандартния изход
пресмятане на обиколка
пресмятане на лице
връщане на типа на триъгълника спрямо страните му (равнобедрен, равностранен, разностранен)
връщане на типа на триъгълника спрямо ъглите му (остроъгълен, правоъгълен, тъпоъгълен)
*/

int main()
{
    Triangle tr;

    readTrianlge(tr);

    printTriangle(tr);

    std::cout << "Perimeter: " << getPerimeter(tr);

    std::cout << std::endl;

    std::cout << "Area: " << getArea(tr);

    std::cout << std::endl;

    TypeTriangleBySidesLength typeOfTriangleBySidesLengths = getTypeOfTriangleBySidesLengths(tr);
    switch (typeOfTriangleBySidesLengths)
    {
    case TypeTriangleBySidesLength::EQUILATERAL: std::cout << "Triangle is equilateral"; break;
    case TypeTriangleBySidesLength::ISOSCELES: std::cout << "Triangle is isosceles"; break;
    case TypeTriangleBySidesLength::SCALENE: std::cout << "Triangle is scalene"; break;
    default: std::cout << "No such triangle";
        break;
    }

    std::cout << std::endl;
    
    TypeTriangleByAngle typeOfTriangleByEdges = getTypeOfTriangleByAngle(tr);
    switch (typeOfTriangleByEdges)
    {
    case TypeTriangleByAngle::ACUTE: std::cout << "Triangle is acute"; break;
    case TypeTriangleByAngle::RIGHT: std::cout << "Triangle is right"; break;
    case TypeTriangleByAngle::OBTUSE: std::cout << "Triangle is obtuse"; break;
    default: std::cout << "No such triangle";
        break;
    }
}

