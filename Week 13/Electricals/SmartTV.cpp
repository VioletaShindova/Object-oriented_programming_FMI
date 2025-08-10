#include "SmartTV.hpp"
#include <iostream>

#pragma warning(disable : 4996)

SmartTV::SmartTV() : SmartTV("unknown", 0) {}

SmartTV::SmartTV(const char* resolution, int inches)
	:Device(), resolution(nullptr), inches(0)
{
	setInches(inches);
	setResolution(resolution);
}

SmartTV::SmartTV(const char* name, const char* producer, double power, bool status, const char* resolution, int inches)
	: Device(name, producer, power, status), resolution(nullptr), inches(0)
{
	setInches(inches);
	setResolution(resolution);
}

SmartTV::SmartTV(const Device& other, const char* resolution, int inches) 
	: Device(other), resolution(nullptr), inches(0)
{
	setInches(inches);
	setResolution(resolution);
}

SmartTV::SmartTV(const SmartTV& other) : Device(other), resolution(other.resolution), inches(other.inches)
{
	copyDynamic(other);
}

SmartTV& SmartTV::operator=(const SmartTV& other)
{
	if (this != &other)
	{
		Device::operator=(other);
		resolution = other.resolution;
		inches = other.inches;

		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

SmartTV::~SmartTV() noexcept
{
	freeDynamic();
}

void SmartTV::setResolution(const char* resolution)
{
	if (!resolution || strlen(resolution) == 0)
		throw std::invalid_argument("Invalid producer\n");

	char* temp = new (std::nothrow) char[strlen(resolution) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, resolution);

	delete[] this->resolution;
	this->resolution = temp;
}

void SmartTV::setInches(int inches)
{
	if (inches < 0)
		throw std::invalid_argument("Inches must be a positive number\n");

	this->inches = inches;
}

Device* SmartTV::clone() const
{
	return new SmartTV(*this);
}

double SmartTV::getPrice() const
{
	return (power * 1.5) + (inches * 20) + (strlen(resolution) * 5);
}

void SmartTV::print(std::ostream& os) const
{
	Device::print(os);

	if (!os.good())
		throw std::runtime_error("Can't open stream\n");

	os << ',' << resolution << ',' << inches << '\n';
}

void SmartTV::freeDynamic()
{
	delete[] resolution;
	resolution = nullptr;
}

void SmartTV::copyDynamic(const SmartTV& other)
{
	char* temp = new (std::nothrow) char[strlen(other.resolution) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, other.resolution);

	resolution = temp;
}
