#pragma once
#include <string>
#include <vector>
#include "Profession.h"

enum class Characteristics {
	INVALID = -1,
	HAPPINESS,
	MONEY,
	LIFE_POINTS
};

class Resident
{
public:
private:
	std::string name;
	std::vector<Characteristics> characteristics;
	std::string schedule;
	Profession* profession;
};

