#include "LivingThings.h"
#pragma warning(disable : 4996)

LivingThings::LivingThings() :LivingThings("unknown", 50, 1000) {}

LivingThings::LivingThings(const char* name, int power, int blood)
	: name(nullptr), power(100), blood(1000), maxBlood(1000)
{
	setPower(power);
	setBlood(blood);
	setName(name);
	setMaxBlood(blood);
}

LivingThings::LivingThings(const LivingThings& other) : power(other.power), blood(other.blood)
{
	copyDynamic(other);
}

LivingThings& LivingThings::operator=(const LivingThings& other)
{
	if (this != &other)
	{
		power = other.power;
		blood = other.blood;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

LivingThings::~LivingThings() noexcept
{
	freeDynamic();
}

void LivingThings::setName(const char* name)
{
	if (!name || strlen(name) == 0)
		throw std::invalid_argument("Invalid name\n");

	char* temp = new (std::nothrow) char[strlen(name) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, name);
	delete[] this->name;
	this->name = temp;
}
void LivingThings::setPower(int power)
{
	if (power < 0)
		throw std::invalid_argument("Invlid power\n");

	this->power = power;
}
void LivingThings::setBlood(int blood)
{
	if (blood < 0)
		throw std::invalid_argument("Invlid blood\n");

	this->blood = blood;
}

void LivingThings::setMaxBlood(int maxBlood)
{
	if (maxBlood <= 0)
		throw std::invalid_argument("Invalid max blood\n");

	this->maxBlood = maxBlood;
}

void LivingThings::freeDynamic()
{
	delete[] name;
	name = nullptr;
}

void LivingThings::copyDynamic(const LivingThings& other)
{
	char* temp = new (std::nothrow) char[strlen(other.name) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, other.name);
	name = temp;
}