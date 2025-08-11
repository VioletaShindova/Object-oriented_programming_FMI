#pragma once
#include "Profession.h"

class Unemployed : public Profession
{
public:
	Unemployed();
	Unemployed(const std::string& name, double salary);

	Profession* clone() const override;
private:
	bool isValidSalary(double salary) const override;
};

