#include <iostream>
#include "Teacher.h"

using std::cin;
using std::cout;
using std::endl;

/*
Напишете клас Teacher, която описва преподавател. Класът трябва да съдържа:

Име (максимум 25 символа)
Възраст (число от 18 до 70)
Предмет (enum с учебни предмети)
Заплата (положително число над 500 лева)
Създайте подходящи конструктори, get и set член-функции.
*/

int main()
{
    Teacher tch1;
	try {
		tch1 = Teacher("Ivan", Teacher::Subjects::MATHEMATICS);
	}
	catch (const std::invalid_argument& inv_arg) {
		cout << inv_arg.what();
	}
	catch (const std::exception& e) {
		cout << e.what();
	}

	tch1.print();
    Teacher tch2(tch1);
	try {
		tch2.setAge(32);
		tch2.setSalary(5000);
	} 
	catch (const std::invalid_argument& inv_arg) {
		cout << inv_arg.what();
	}
	
	tch2.print();
	cout << "Age of teacher 1: " << tch1.getAge();
}
