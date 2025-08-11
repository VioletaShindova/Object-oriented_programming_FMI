#pragma once
#include "Profession.h"

class Miner : public Profession
{
public:
	Miner();
	Miner(const std::string& name, double salary);

	Profession* clone() const override;
private:
	bool isValidSalary(double salary) const override;
};

