#include "Smartphone.hpp"
#include <iostream>
#pragma warning(disable : 4996)

Smartphone::Smartphone() : Smartphone("unknown", "unknown", 0, "unknown", 0) {}

Smartphone::Smartphone(const char* model, const char* brand, double price, const char* operatingSystem, int ram)
	: Phone(model, brand, price), operatingSystem(nullptr), ram(0)
{
	setRAM(ram);
	setOperatingSystem(operatingSystem);
}

Smartphone::Smartphone(const Phone& other, const char* operatingSystem, int ram) 
	: Phone(other), operatingSystem(nullptr), ram(0)
{
	setRAM(ram);
	setOperatingSystem(operatingSystem);
}

Smartphone::Smartphone(const Smartphone& other) 
	: Phone(other), ram(other.ram)
{
	copyDynamic(other);
}

Smartphone& Smartphone::operator=(const Smartphone& other)
{
	if (this != &other)
	{
		Phone::operator=(other);
		ram = other.ram;
		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

Smartphone::~Smartphone() noexcept
{
	freeDynamic();
}

void Smartphone::setOperatingSystem(const char* operatingSystem)
{
	if (!operatingSystem || strlen(operatingSystem) == 0)
		throw std::invalid_argument("Invalid opertaing system\n");

	char* temp = new (std::nothrow) char[strlen(operatingSystem) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, operatingSystem);

	delete[] this->operatingSystem;
	this->operatingSystem = temp;
}

void Smartphone::setRAM(int ram)
{
	if (ram < 0)
		throw std::invalid_argument("RAM must be a positive number\n");

	this->ram = ram;
}

void Smartphone::calculatePrice() const
{
	price += ram;
}

void Smartphone::freeDynamic()
{
	delete[] operatingSystem;
	operatingSystem = nullptr;
}

void Smartphone::copyDynamic(const Smartphone& other)
{
	char* temp = new (std::nothrow) char[strlen(other.operatingSystem) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, other.operatingSystem);

	delete[] operatingSystem;
	operatingSystem = nullptr;
}
