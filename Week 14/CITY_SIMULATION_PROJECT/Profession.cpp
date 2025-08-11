#include "Profession.h"

Profession::Profession() : Profession("unemployed", 0) {}

Profession::Profession(const std::string& name, double salary)
{
	setProfessionName(name);
	setSalary(salary);
}

void Profession::setProfessionName(const std::string& name)
{
	if (name.empty())
		throw std::invalid_argument("Invalid name\n");

	professionName = name;
}

void Profession::setSalary(double salary)
{
	if (!isValidSalary(salary))
		throw std::invalid_argument("Invalid salary");

	this->salary = salary;
}

const std::string& Profession::getProfessionName() const noexcept
{
	return professionName;
}

double Profession::getSalary() const noexcept
{
	return salary;
}
