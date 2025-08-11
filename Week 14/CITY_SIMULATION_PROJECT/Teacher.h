#pragma once
#include "Profession.h"

class Teacher : public Profession
{
public:
	Teacher();
	Teacher(const std::string& name, double salary);

	Profession* clone() const override;
private:
	bool isValidSalary(double salary) const override;
};

