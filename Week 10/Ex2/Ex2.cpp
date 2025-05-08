// Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MyString.h"
#include "Student.h"
#include "StudentDB.h"
#include "SortedStudentDB.h"
#include "FilteredStudentDB.h"

using std::cin;
using std::cout;
using std::endl;

/*
Създайте клас Student, който съдържа следната информация:

име (от тип MyString);
факултетен номер (от тип unsigned);
курс, в който учи (от тип unsigned).

Да се реализира клас StudentDB, който представлява база от данни за съхранение на информацията за студенти. Класът да поддържа
следните функционалности:
add - добавяне студент в базата;
remove - премахване на студент от базата по подаден факултетен номер;
find - търсене на студент в базата по подаден факултетен номер;
display - визуализира информация за базата данни.

Да се реализира клас SortedStudentDB, който наследява StudentDB и поддържа следната допълнителна функционалност:
sortBy - запазва студентите сортирани по подаден критерий;

Да се реализира клас FilteredStudentDB, който наследява StudentDB и поддържа следните допълнителни функционалности:
filter - по подаден критерий запазва в базата данни само студентите, които го изпълняват;
limit - по подаден брой N запазва само първите N студенти в базата.
*/

int main()
{
	Student st1{ "Anabel", 1 };
	Student st2{ "Yulian", 4 };
	Student st3{ "Zebra", 2 };
	Student st4{ "Boris", 1 };
	Student st5{ "Cveti", 1 };
	Student st6{ "Darina", 3 };

	Student* students = new Student[6];
	students[0] = st1;
	students[1] = st2;
	students[2] = st3;
	students[3] = st4;
	students[4] = st5;
	students[5] = st6;
	StudentDB stdb(students, 6);

	SortedStudentDB sstdb(stdb);

	sstdb.sortBy([](const Student& lhs, const Student& rhs) {return lhs.getName() < rhs.getName();});

	//cout << sstdb;

	FilteredStudentDB fstdb(sstdb);
	//std::cout << fstdb;
	fstdb.filter([](const Student& st) {return st.getCourse() == 1;});

	std::cout << fstdb;
}

