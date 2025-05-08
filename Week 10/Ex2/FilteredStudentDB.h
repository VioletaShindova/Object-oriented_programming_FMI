#pragma once
#include "StudentDB.h"
#include <iostream>

class FilteredStudentDB : public StudentDB
{
public:
	FilteredStudentDB();
	FilteredStudentDB(const Student* students, size_t size, size_t capacity);
	FilteredStudentDB(const FilteredStudentDB& other);
	FilteredStudentDB(const StudentDB& other);
	FilteredStudentDB& operator=(const FilteredStudentDB& other);

	~FilteredStudentDB();

	void filter(bool (*pred)(const Student& st));
	void limit(size_t numberOfStudents);
private:

};

