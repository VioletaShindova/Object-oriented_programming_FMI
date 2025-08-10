#include "Device.hpp"
#include <iostream>
#pragma warning(disable : 4996)

Device::Device() : Device("unknown", "unknown") {}

Device::Device(const char* name, const char* producer, double power, bool status)
	:name(nullptr), producer(nullptr), power(0), status(status)
{
	setPower(power);
	setName(name);

	try {
		setProducer(producer);
	}
	catch (const std::bad_alloc& bad_alloc)
	{
		delete[] this->name;
		std::cout << "Bad allocation\n";
		throw bad_alloc;
	}
	catch (const std::invalid_argument& inv_arg)
	{
		delete[] this->name;
		std::cout << inv_arg.what();
		throw inv_arg;
	}
}

Device::Device(const Device& other)
	: power(other.power), status(other.status)
{
	copyDynamic(other);
}

Device& Device::operator=(const Device& other)
{
	if (this != &other)
	{
		power = other.power;
		status = other.status;

		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Device::~Device() noexcept
{
	freeDynamic();
}

void Device::setName(const char* name)
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

void Device::setProducer(const char* producer)
{
	if (!producer || strlen(producer) == 0)
		throw std::invalid_argument("Invalid producer\n");

	char* temp = new (std::nothrow) char[strlen(producer) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, producer);

	delete[] this->producer;
	this->producer = temp;
}

void Device::setPower(double power)
{
	if (power < 0)
		throw std::invalid_argument("Power must be a positive number\n");

	this->power = power;
}

void Device::setStatus(bool status)
{
	this->status = status;
}

void Device::print(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Can't open stream\n");

	os << name << ',' << producer << ',' << power << ',' << status;
}

void Device::freeDynamic()
{
	delete[] name;
	delete[] producer;

	name = nullptr;
	producer = nullptr;
}

void Device::copyDynamic(const Device& other)
{
	char* tempName = new (std::nothrow) char[strlen(other.name) + 1];

	if (!tempName)
		throw std::bad_alloc();

	strcpy(tempName, other.name);

	char* tempProducer = new (std::nothrow) char[strlen(other.producer) + 1];

	if (!tempProducer)
	{
		delete[] tempName;
		throw std::bad_alloc();
	}

	strcpy(tempProducer, other.producer);

	name = tempName;
	producer = tempProducer;
}
