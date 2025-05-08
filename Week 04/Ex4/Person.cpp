#include "Person.h"
#include <iostream>
#include <fstream>
#define MIN(a, b) (a < b) ? a : b

size_t getFileSize(std::ifstream& ifs) {
	int currPosition = ifs.tellg();

	ifs.seekg(0, std::ios::end);

	int result = ifs.tellg();

	ifs.seekg(currPosition, std::ios::beg);

	return result;
}

PeopleService::Person::Person(const char name[], size_t nameSize, int salary) {
	if (!setName(name, nameSize))
		throw "Invalid name or size!";

	if (!setSalary(salary))
		throw "Invalid salary!";
}

bool PeopleService::Person::setName(const char name[], size_t nameSize) {
	if (!isValidSize(nameSize))
		return false;

	strcpy_s(this->name, name);
	this->name[nameSize] = '\0';
	return true;
}

bool PeopleService::Person::setSalary(int salary) {
	if (!isValidSalary(salary))
		return false;

	this->salary = salary;
	return true;
}

unsigned PeopleService::Person::getSalary() const {
	return this->salary;
}

bool PeopleService::Person::isValidSize(size_t nameSize) const {
	return 0 < nameSize && nameSize <= MAX_SIZE_FOR_NAME;
}

bool PeopleService::Person::isValidSalary(int salary) const {
	return 0 < salary;
}

void PeopleService::Person::print() const {
	std::cout << this->name << ' ' << this->salary << std::endl;
}

PeopleService::PeopleService(int size) {
	if(!setSize(size))
		throw "Invalid size";
		
	this->people = new Person[size];
}

PeopleService::PeopleService(const Person* people, int size) {
	this->people = new (std::nothrow) Person[size];
	if (!this->people || !people)
		throw "Invalid size";

	for (size_t i = 0; i < size; i++)
	{
		this->people[i] = people[i];
	}
	this->size = size;
	findAvgSalary();
}

PeopleService::PeopleService(const PeopleService& other) : size(other.size), avgSalary(other.avgSalary) {
	copyDynamic(other);
}

PeopleService& PeopleService::operator=(const PeopleService& other) {
	if (this != &other) {
		freeDynamic();
		copyDynamic(other);
		avgSalary = other.avgSalary;
		this->size = other.size;
	}

	return *this;
}

PeopleService::~PeopleService() {
	freeDynamic();
}

bool PeopleService::setSize(int size) {
	if (!isValidSize(size))
		return false;

	this->size = size;
}

void PeopleService::printPeopleAndTheirSalaries() const {
	for (size_t i = 0; i < this->size; i++)
		this->people[i].print();
}

void PeopleService::printAvgSalary() const {
	std::cout << "Average salary: " << this->avgSalary << std::endl;
}

bool PeopleService::writeToBinaryFile(const char* fileName) const {
	if (!fileName)
		return false;

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
		return false;

	ofs.write((const char*)this->people, sizeof(Person) * this->size);

	ofs.close();
	return true;
}

bool PeopleService::readFromBinaryFile(const char* fileName) {
	if (!fileName)
		return false;

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
		return false;

	ifs.read((char*)this->people, MIN(getFileSize(ifs), (size_t)sizeof(Person) * this->size));

	ifs.close();
	return true;
}

void PeopleService::findAvgSalary() {
	for (size_t i = 0; i < this->size; i++)
		this->avgSalary += this->people[i].getSalary();

	this->avgSalary /= this->size;
}

bool PeopleService::isValidSize(int size) const {
	return 0 < size;
}

void PeopleService::copyDynamic(const PeopleService& other) {
	this->people = new Person[other.size];

	for (size_t i = 0; i < other.size; i++)
		this->people[i] = other.people[i];
}

void PeopleService::freeDynamic() {
	delete[] people;
}