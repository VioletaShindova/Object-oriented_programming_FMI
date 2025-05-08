#pragma once
#include "MyString.h"
#include <iostream>

class Student
{
public:
	Student();

	Student(const MyString& name, int course);

	void setCourse(int course);

	const MyString& getName() const;

	unsigned getFN() const;

	unsigned getCourse() const;

	friend bool operator==(const Student& lhs, const Student& rhs);
	friend bool operator!=(const Student& lhs, const Student& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Student& obj);
	friend std::istream& operator>>(std::istream& is, Student& obj);

private:
	bool checkCourse(int course) const;

	MyString name;
	unsigned fn;
	unsigned course;

	static unsigned facultyNumber;
};