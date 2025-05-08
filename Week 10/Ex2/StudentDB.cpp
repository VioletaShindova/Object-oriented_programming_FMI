#include "StudentDB.h"

StudentDB::StudentDB() : StudentDB({}, 0, 1) {}

StudentDB::StudentDB(const Student* students = {}, int size = 0, int capacity = 10) {
	setCapacity(capacity);
	setSize(size);
	setStudents(students, capacity);
}

StudentDB::StudentDB(const StudentDB& other) : size(other.size), capacity(other.capacity) {
	copyDynamic(other);
}

StudentDB& StudentDB::operator=(const StudentDB& other) {
	if (this != &other) {
		size = other.size;
		capacity = other.capacity;
		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

StudentDB::~StudentDB() {
	freeDynamic();
}

void StudentDB::setCapacity(int capacity) {
	if (capacity < 1)
		throw std::invalid_argument("Invalid capacity!");

	this->capacity = capacity;
}
void StudentDB::setSize(int size) {
	if (size < 0 || size >= capacity)
		throw std::invalid_argument("Invalid size!");

	this->size = size;
}

void StudentDB::setStudents(const Student* students, size_t size) {
	this->students = new (std::nothrow) Student[size];
	if (!students || !this->students)
		throw std::out_of_range("Not enough memory!");

	for (size_t i = 0; i < this->size; i++)
		this->students[i] = students[i];

	for (size_t i = this->size; i < size; i++)
		this->students[i] = Student();
}

const Student* StudentDB::getStudents() const {
	return students;
}

size_t StudentDB::getSize() const {
	return size;
}

void StudentDB::add(const Student& newStudent) {
	if (size + 1 >= capacity)
		resize();

	students[size++] = newStudent;
}

void StudentDB::remove(const Student& newStudent) {
	bool isFound = false;

	for (size_t i = 0; i < size; i++) {
		if (students[i] == newStudent) {
			std::swap(students[i], students[size - 1]);
			isFound = true;
		}
	}
	if (!isFound)
		return;

	size -= 1;
	Student* studentsTemp = new Student[size];

	for (size_t i = 0; i < size; i++)
		studentsTemp[i] = students[i];

	freeDynamic();
	students = studentsTemp;
}

bool StudentDB::find(unsigned fn) const {
	for (size_t i = 0; i < size; i++) {
		if (students[i].getFN() == fn)
			return true;
	}
	return false;
}

void StudentDB::display() const {
	for (size_t i = 0; i < size; i++) {
		std::cout << students[i] << ' ';
	}

	std::cout << std::endl;
}

void StudentDB::freeDynamic() {
	delete[] students;
	students = nullptr;
}

void StudentDB::copyDynamic(const StudentDB& other) {
	students = new Student[other.size];

	for (size_t i = 0; i < other.size; i++)
		students[i] = other.students[i];
}

void StudentDB::resize() {
	size_t capacityTemp = capacity * 2;
	Student* studentsTemp = new Student[capacityTemp];

	for (size_t i = 0; i < capacityTemp; i++)
		studentsTemp[i] = students[i];

	freeDynamic();
	students = studentsTemp;
	size = capacity;
	capacity = capacityTemp;
}

std::ostream& operator<<(std::ostream& os, const StudentDB& stdb)
{
	os <<"size: " <<  stdb.size << '\n';
	for (size_t i = 0; i < stdb.size; i++)
		os << stdb.students[i] << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, StudentDB& stdb)
{
	is >> stdb.size;

	stdb.freeDynamic();
	stdb.students = new Student[stdb.size];

	for (size_t i = 0; i < stdb.size; i++)
		is >> stdb.students[i];

	is >> stdb.capacity;
	return is;
}
