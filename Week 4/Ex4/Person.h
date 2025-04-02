#pragma once

constexpr size_t MAX_SIZE_FOR_NAME = 3;

class PeopleService {
public:
	struct Person {
	public:
		Person() = default;

		Person(const char name[], size_t nameSize, int salary);

		bool setName(const char name[], size_t nameSize);

		bool setSalary(int salary);

		unsigned getSalary() const;

		void print() const;

	private:
		bool isValidSize(size_t nameSize) const;

		bool isValidSalary(int salary) const;

		char name[MAX_SIZE_FOR_NAME] = "";
		unsigned salary = 0;
	};

	PeopleService() = default;

	explicit PeopleService(int size);

	PeopleService(const Person* people, int size);

	PeopleService(const PeopleService& other);

	PeopleService& operator=(const PeopleService& other);

	~PeopleService();

	bool setSize(int size);

	void printPeopleAndTheirSalaries() const;

	void printAvgSalary() const;

	bool writeToBinaryFile(const char* fileName) const;

	bool readFromBinaryFile(const char* fileName);

private:
	void findAvgSalary();

	bool isValidSize(int size) const;

	void copyDynamic(const PeopleService& other);

	void freeDynamic();

	Person* people = nullptr;
	size_t size = 0;
	double avgSalary = 0;
};