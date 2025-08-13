#include "Drink.hpp"
#include "Bar.hpp"
#pragma warning(disable : 4996)

Drink::Drink() : Drink("unknown", 0) {}

Drink::Drink(const char* name, int ml)
	: name(nullptr), ml(0)
{
	setML(ml);
	setName(name);
}

Drink::Drink(const Drink& other) : ml(other.ml)
{
	copyDynamic(other);
}

Drink& Drink::operator=(const Drink& other)
{
	if (this != &other)
	{
		ml = other.ml;

		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Drink::~Drink() noexcept
{
	freeDynamic();
}

static bool areValidLatinSymbols(const char* name)
{
	if (!name)
		throw std::invalid_argument("Empty name\n");

	bool res = true;

	while (*name)
	{
		if ((*name) < 'a' || (*name) > 'z')
		{
			res = false;
			break;
		}
		name++;
	}
	return res;
}

static bool isValidName(const char* name)
{
	return name && (*name) >= 'A' && (*name) <= 'Z' && areValidLatinSymbols(name + 1);
}

void Drink::setName(const char* name)
{
	if (!name || !strlen(name) || !isValidName(name))
		throw std::invalid_argument("Invalid name\n");

	char* temp = new (std::nothrow) char[strlen(name) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, name);
	delete[] this->name;
	this->name = temp;
}

void Drink::setML(int ml)
{
	if (ml < 200 || ml > 1000)
		throw std::invalid_argument("ML must be between 200 and 1000\n");

	this->ml = ml;
}

void Drink::setCounOfEachDrink(int count)
{
	if (countOfEachDrink + count < 0)
		throw std::logic_error("There are less than 0 bottles\n");

	countOfEachDrink += count;
}

void Drink::freeDynamic()
{
	delete[] name;
	name = nullptr;
}

void Drink::copyDynamic(const Drink& other)
{
	char* temp = new (std::nothrow) char[strlen(other.name) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, other.name);
	name = temp;
}

bool operator==(const Drink& lhs, const Drink& rhs)
{
	return strcmp(lhs.name, rhs.name) == 0 &&
		lhs.ml == rhs.ml;
}

bool operator!=(const Drink& lhs, const Drink& rhs)
{
	return !(lhs == rhs);
}
