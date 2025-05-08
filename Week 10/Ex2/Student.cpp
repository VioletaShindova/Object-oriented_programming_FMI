#include "Student.h"

unsigned Student::facultyNumber = 0;
  
Student::Student() : Student("Pesho", 1) {}

Student::Student(const MyString& name, int course) : name(name) {
	setCourse(course);
	fn = facultyNumber++;
}

void Student::setCourse(int course) {
	if (!checkCourse(course))
		throw std::invalid_argument("Course must be between 1 and 4");

	this->course = course;
}

const MyString& Student::getName() const {
	return name;
}

unsigned Student::getFN() const {
	return fn;
}

unsigned Student::getCourse() const {
	return course;
}

bool Student::checkCourse(int course) const {
	return (1 <= course) && (course <= 4); //bachelor degree
}

bool operator==(const Student& lhs, const Student& rhs) {
	return (lhs.name == rhs.name) &&
		(lhs.fn == rhs.fn) &&
		(lhs.course == rhs.course);
}

bool operator!=(const Student& lhs, const Student& rhs) {
	return !((lhs.name == rhs.name) &&
		(lhs.fn == rhs.fn) &&
		(lhs.course == rhs.course));
}

std::ostream& operator<<(std::ostream& os, const Student& obj) {
	os << obj.name << ' ' << obj.course;
	return os;
}

std::istream& operator>>(std::istream& is, Student& obj) {
	is >> obj.name >> obj.course;
	return is;
}