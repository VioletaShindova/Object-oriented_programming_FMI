// Ex1_BG_Date.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BulgarianDate.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	BulgarianDate bg1;
	try {
		bg1 = BulgarianDate(1, 4, 1916);
	}
	catch (const std::out_of_range& oor) {
		cout << oor.what();
	}

	bg1.print();
	bg1.goToNextDay();
	bg1.print();

	BulgarianDate bg2(31, 3, 1916);
	bg2.goToNextDay();
	bg2.print();

	cout << compareBulgarianDates(bg1, bg2);
}

