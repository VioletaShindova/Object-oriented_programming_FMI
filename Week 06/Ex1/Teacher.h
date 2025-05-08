#pragma once

constexpr size_t MAX_SIZE_OF_NAME = 25;

class Teacher
{
public:
	enum class Subjects {
		INVALID = -1,
		ENGLISH,
		MATHEMATICS,
		BIOLOGY,
		PHYSICS,
		HISTORY,
		SCIENCE,
		COUNT_OF_SUBJECT
	};

	Teacher() : age(18) {}

	Teacher(const char* name, int age);

	Teacher(const char* name, Subjects subject);

	Teacher(const char* name, int age, int salary);

	Teacher(const char* name, int age, Subjects subject, int salary);

	void setName(const char* name);

	void setAge(int age);

	void setSubject(Subjects subject);

	void setSalary(int salary);

	const char* getName() const;

	//uint8_t getAge() const;
	unsigned getAge() const;

	const Subjects& getSubject() const;

	unsigned getSalary() const;

	void print() const;

private:
	bool isValidName(const char* name) const;

	bool isValidAge(int age) const;

	bool isValidSubject(Subjects subject) const;

	bool isValidSalary(int salary) const;

	char name[MAX_SIZE_OF_NAME] = "";
	//uint8_t age : 3;
	unsigned age = 18;
	Subjects subject = Subjects::INVALID;
	unsigned salary = 500;
};

