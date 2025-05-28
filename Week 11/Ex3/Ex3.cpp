// Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "Prize.h"
#include "Sylvester.h"
#include "SquidWard.h"
#include "ComputerBoy.h"
#include "Pacman.h"
#include "Penguin.h"
/*
Реализирайте йерархия, описваща награди, които нашия потребител може да си купи. 
За целта напишете абстрактен клас Prize, който описва някаква награда. 
Всяка награда има цена и точки, които трябва да дадем, за да я получим. 
Също така всяка награда има функция visualize(), която показва на стандартния изход каква точно е нашата награда.

Наградите, с които разполагаме, са

Penguin - 50 точки
Pacman - 150 точки
computerBoy - 500 точки
squidward - 1000 точки
sylvester - 1500 точки
Визуализацията на награда представлява текстов файл и всяка награда има точно една визуализация.
*/

int main()
{
	Prize** ptr = new Prize * [5];

	ptr[0] = new Penguin();
	ptr[1] = new Pacman(1,2);
	ptr[2] = new ComputerBoy(2,3);
	ptr[3] = new SquidWard(1, 4);
	ptr[4] = new Sylvester(2, 1500);

	std::ofstream ofs("file.txt");

	ptr[0]->visualize(ofs);
	ptr[1]->visualize(ofs);
	ptr[2]->visualize(ofs);
	ptr[3]->visualize(ofs);
	ptr[4]->visualize(ofs);

	delete ptr[4];
	delete ptr[3];
	delete ptr[2];
	delete ptr[1];
	delete ptr[0];

	delete[] ptr;
}
