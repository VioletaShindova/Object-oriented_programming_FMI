#pragma once
#include "Profession.h"

class Programmer : public Profession
{
public:
	Programmer();
	Programmer(const std::string& name, double salary);

	Profession* clone() const override;
private:
	bool isValidSalary(double salary) const override;
};

