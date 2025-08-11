#pragma once
#include <iostream>
#include <string>

class Profession
{
public:
	Profession();
	Profession(const std::string& name, double salary);
	virtual ~Profession() noexcept = default;

	virtual Profession* clone() const = 0;

	void setProfessionName(const std::string& name);
	void setSalary(double salary);
	
	const std::string& getProfessionName() const noexcept;
	double getSalary() const noexcept;

private:
	virtual bool isValidSalary(double salary) const = 0;

	std::string professionName;
	double salary;
};

