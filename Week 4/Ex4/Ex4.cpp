// Ex4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Person.h"

using std::cin;
using std::cout;
using std::endl;

/*
Имате двоичния файл people.dat. В него се пази последователно следната информация за произволен брой хора:

име, което е максимално 23 символа
каква заплата изкарват от тип unsigned
Да се имплементират следните функционалности:

Отпечатване на хората, които изкарват над средната заплата
Добавяне на човек във файла people.dat
*/

int main()
{
	int countOfPeople;
	cin >> countOfPeople;

	PeopleService::Person* people{};
	try {
		people = new PeopleService::Person[countOfPeople];
	}
	catch (const std::exception& e) {
		cout << e.what();
	}

	/*for (size_t i = 0; i < countOfPeople; i++) {
		cout << "Name: ";
		char name[MAX_SIZE_FOR_NAME + 4];
		cin >> name;	
		cout << "Salary: ";
		int salary;
		cin >> salary;
		people[i] = PeopleService::Person(name, strlen(name), salary);
	}*/

	PeopleService obj1(people, countOfPeople);
	obj1.printAvgSalary();

	if (!obj1.writeToBinaryFile("people.dat")) {
		return 0;
	}

	PeopleService obj2(obj1);
	if (!obj2.readFromBinaryFile("people.dat")) {
		return 0;
	}

	obj2.printPeopleAndTheirSalaries();
}

