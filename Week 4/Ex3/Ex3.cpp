// Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CoordinationSystem.h"

using std::cout;
using std::cin;
using std::endl;

/*
Да се напише програма, която чете двоичен файл, съдържащ неопределен брой двойки стойности (x, y), 
представляващи координати в декартова координатна система. 
След прочитането на данните да се изчисли центърът на тежестта на всички точки. 
След това да се намерят трите най-близки точки до центъра на тежестта и техните координати да се запишат в нов двоичен файл.
*/

int main()
{
    int countOfPairsSize;
    cout << "Input countOfPairsSize: ";
    cin >> countOfPairsSize;
    
    CoordinationSystem obj1;
    CoordinationSystem::Pair* pairs{};
    try {
        pairs = new CoordinationSystem::Pair[countOfPairsSize];
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
        return -1;
    }
     

    cout << "Input coordinates of points: " << endl;
    for (size_t i = 0; i < countOfPairsSize; i++)
    {
        double x, y;
        cin >> x >> y;
        pairs[i] = CoordinationSystem::Pair(x, y);
    }

    try {
        obj1 = CoordinationSystem(pairs, countOfPairsSize);
    }
    catch (const std::exception& e) {
        std::cout << "Invalid name or size!";
    }

    if (!obj1.writeToBinaryFile("ex3_binaryFile.txt"))
        return -1;


    CoordinationSystem::Pair* pairs2 = new (std::nothrow) CoordinationSystem::Pair[countOfPairsSize];
    CoordinationSystem obj2(CoordinationSystem(pairs2, countOfPairsSize));
    if(!obj2.readFromBinaryFile("ex3_binaryFile.txt"))
        return -1;

    obj2.print();

    obj1.getCenterOfGravity();
    CoordinationSystem::Pair* pairs3 = obj1.getTheThreeClosestPointsToTheCenter();
    CoordinationSystem obj3(pairs3, obj1.getSize());
    obj3.printFirstThreePoints();
}

