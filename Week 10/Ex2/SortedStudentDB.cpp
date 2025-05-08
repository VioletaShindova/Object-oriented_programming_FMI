#include "SortedStudentDB.h"

SortedStudentDB::SortedStudentDB() {}

SortedStudentDB::SortedStudentDB(const Student* students, int size, int capacity) : StudentDB(students, size, capacity) {}

SortedStudentDB::SortedStudentDB(const StudentDB& other) : StudentDB(other) {
	copyDynamic(other);
}

SortedStudentDB& SortedStudentDB::operator=(const SortedStudentDB& other) {
	if (this != &other) {
		StudentDB::operator=(other);
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

SortedStudentDB::~SortedStudentDB() {
	freeDynamic();
}

void SortedStudentDB::sortBy(bool (*isLess)(const Student&, const Student&)) {

	for (size_t i = 0; i < size - 1; i++)
	{
		size_t currMin = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (isLess(students[j], students[currMin]))
				currMin = j;
		}
		if (currMin != i)
			std::swap(students[i], students[currMin]);
	}
}