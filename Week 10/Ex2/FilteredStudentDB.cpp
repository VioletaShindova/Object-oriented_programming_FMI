#include "FilteredStudentDB.h"
#include <iostream>

FilteredStudentDB::FilteredStudentDB() : StudentDB() {}

FilteredStudentDB::FilteredStudentDB(const Student* students, size_t size, size_t capacity) : StudentDB(students, size, capacity) {}

FilteredStudentDB::FilteredStudentDB(const FilteredStudentDB& other) : StudentDB(other) {
	copyDynamic(other);
}

FilteredStudentDB::FilteredStudentDB(const StudentDB& other) : StudentDB(other) {
	copyDynamic(other);
}

FilteredStudentDB& FilteredStudentDB::operator=(const FilteredStudentDB& other) {
	if (this != &other) {
		size = other.size;
		capacity = other.capacity;
		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

FilteredStudentDB::~FilteredStudentDB() {
	freeDynamic();
}

void FilteredStudentDB::filter(bool (*pred)(const Student& st)) {
	size_t tempSize = 0;
	for (size_t i = 0; i < size; i++) {
		if (pred(students[i]))
			tempSize++;
	}

	Student* tempStudents = new Student[tempSize * 2];
	for (size_t i = 0; i < size; i++) {
		if (pred(students[i]))
			tempStudents[i] = students[i];
	}

	//StudentDB::freeDynamic();
	delete[] students;
	students = tempStudents;
	size = tempSize;
	capacity = size * 2;
}

void FilteredStudentDB::limit(size_t numberOfStudents) {
	Student* tempStudents = new Student[numberOfStudents * 2];

	for (size_t i = 0; i < numberOfStudents; i++)
		tempStudents[i] = students[i];

	delete[] students;
	students = tempStudents;
	size = numberOfStudents;
	capacity = size * 2;
}
