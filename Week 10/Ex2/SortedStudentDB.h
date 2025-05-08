#pragma once
#include "StudentDB.h"

class SortedStudentDB : public StudentDB
{
public:
	SortedStudentDB();

	SortedStudentDB(const Student* students, int size);

	SortedStudentDB(const StudentDB& other);

	//SortedStudentDB& operator=(const SortedStudentDB& other);

	//~SortedStudentDB();

	void sortBy(bool (*pred)(const Student&, const Student&));

private:

};

