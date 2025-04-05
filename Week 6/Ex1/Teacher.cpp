#include "Teacher.h"
#include <iostream>
#pragma warning (disable: 4996)

Teacher::Teacher(const char* name, int age) {
	setName(name);
	setAge(age);
}

Teacher::Teacher(const char* name, Subjects subject) {
	setName(name);
	setSubject(subject);
}

Teacher::Teacher(const char* name, int age, int salary) {
	setName(name);
	setAge(age);
	setSalary(salary);
}

Teacher::Teacher(const char* name, int age, Subjects subject, int salary) {
	setName(name);
	setAge(age);
	setSubject(subject);
	setSalary(salary);
}

void Teacher::setName(const char* name) {
	if (!isValidName(name))
		throw std::exception("Invalid name!");

	strcpy(this->name, name);
}

void Teacher::setAge(int age) {
	if (!isValidAge(age))
		throw std::invalid_argument("Invalid age!");

	this->age = age;
}

void Teacher::setSubject(Subjects subject) {
	if (!isValidSubject(subject))
		throw std::invalid_argument("Invalid subject");

	this->subject = (Subjects)subject;
}

void Teacher::setSalary(int salary) {
	if (!isValidSalary(salary))
		throw std::invalid_argument("Invalid salary!");

	this->salary = salary;
}

const char* Teacher::getName() const {
	char* temp = new char[strlen(this->name) + 1];
	strcpy(temp, this->name);
	return temp;
}

//uint8_t Teacher::getAge() const {
//	return this->age;
//}

unsigned Teacher::getAge() const {
	return this->age;
}

const Teacher::Subjects& Teacher::getSubject() const {
	return this->subject;
}

unsigned Teacher::getSalary() const {
	return this->salary;
}

void Teacher::print() const {
	std::cout << this->name << ' ' << this->age << ' ' << (int)this->subject << ' ' << this->salary << std::endl;
}

bool Teacher::isValidName(const char* name) const {
	return name && (0 < strlen(name) && (strlen(name) <= MAX_SIZE_OF_NAME));
}

bool Teacher::isValidAge(int age) const {
	return (18 <= age) && (age <= 70);
}

bool Teacher::isValidSubject(Subjects subject) const {
	return  (-1 <= (int)subject) && ((int)subject < (int)Subjects::COUNT_OF_SUBJECT);
}

bool Teacher::isValidSalary(int salary) const {
	return (500 <= salary);
}