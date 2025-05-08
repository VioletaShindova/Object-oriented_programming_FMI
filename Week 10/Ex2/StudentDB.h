#pragma once
#include "Student.h"
#include <exception>
#include <iostream>

class StudentDB
{
public:
	StudentDB();

	StudentDB(const Student* students, int size, int capacity);

	StudentDB(const StudentDB& other);

	StudentDB& operator=(const StudentDB& other);

	~StudentDB();

	void setCapacity(int capacity);

	void setSize(int size);
	
	void setStudents(const Student* students, size_t size);

	const Student* getStudents() const;
		
	size_t getSize() const;

	void add(const Student& newStudent);

	void remove(const Student& newStudent);

	bool find(unsigned fn) const;

	void display() const;

	friend std::ostream& operator<<(std::ostream& os, const StudentDB& stdb);
	friend std::istream& operator>>(std::istream& os, StudentDB& stdb);

protected:
	void freeDynamic();

	void copyDynamic(const StudentDB& other);

	void resize();

	Student* students;
	size_t size;
	size_t capacity;
};

