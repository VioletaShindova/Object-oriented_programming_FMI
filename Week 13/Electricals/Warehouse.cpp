#include "SmartWasher.hpp"
#include "Warehouse.hpp"
#include "Device.hpp"
#include "Laptop.hpp"
#include "SmartTV.hpp"
#include <iostream>

Warehouse::Warehouse() : Warehouse(1) {}

Warehouse::Warehouse(int capacity) 
	: devices(nullptr), size(0), capacity(1), currPower(1)
{
	setCapacity(capacity);
}

Warehouse::Warehouse(const Warehouse& other) 
	: size(other.size), capacity(other.capacity), currPower(other.currPower)
{
	copyDynamic(other);
}

Warehouse& Warehouse::operator=(const Warehouse& other)
{
	if (this != &other)
	{
		size = other.size;
		capacity = other.capacity; 
		currPower = other.currPower;

		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

Warehouse::~Warehouse() noexcept
{
	freeDynamic();
}

void Warehouse::setCapacity(int capacity)
{
	if (capacity < 0)
		throw std::invalid_argument("Invalid capacity\n");

	size_t tempSize = capacity * 2 + 1;

	Device** temp = new (std::nothrow) Device * [tempSize];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
		temp[i] = devices[i] ? devices[i]->clone() : nullptr;

	for (size_t i = 0; i < size; i++)
	{
		delete devices[i];
	}
	delete[] devices;
	devices = temp;

	this->capacity = (capacity * 2) + 1;
	size = capacity;
}

bool Warehouse::addDevice(const Device* device)
{
	if (!device)
		throw std::invalid_argument("Invalid device\n");

	if (size + 1 > capacity)
		resize();

	devices[size++] = device->clone();

	return true;
}

enum class DeviceType
{
	INVALID = -1,
	LAPTOP,
	SMARTTV
};

bool Warehouse::addDevice(const char* name, const char* producer)
{
	if (!name || !strlen(name) || !producer || !strlen(producer))
		throw std::invalid_argument("Invalid argument/s\n");

	if (size + 1 > capacity)
		resize();

	using std::cin;
	using std::cout;

	int number = 0;

	do {
		if (!cin)
		{
			cin.clear();
			cin.sync();
		}
		cout << "Type: 0-Laptop, 1-SmartTV\n";
		cin >> number;
	} while (!std::cin || number < 0 || number > 1);
	

	Device* temp = nullptr;

	switch (static_cast<DeviceType>(number))
	{
	case DeviceType::LAPTOP:
		temp = new (std::nothrow) Laptop(name, producer);
		break;
	case DeviceType::SMARTTV:
		temp = new (std::nothrow) SmartTV(name, producer);
		break;
	default:
		throw std::logic_error("Can't add invalid device\n");
	}

	if (!temp)
		return false;

	devices[size++] = temp;
	return true;
}

bool Warehouse::turnOn(const char* name)
{
	if (!name || !strlen(name))
		throw std::invalid_argument("Invalid name\n");

	bool result = false;
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(devices[i]->getName(), name) == 0 && !devices[i]->getStatus())
		{
			devices[i]->setStatus(true);
			result = true;
		}
	}
	return result;
}

double Warehouse::getTotalPrice() const
{
	double res = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (devices[i])
			res += devices[i]->getPrice();
	}
	return res;
}

void Warehouse::printAll() const
{
	for (size_t i = 0; i < size; i++)
	{
		if (devices[i])
			devices[i]->print(std::cout);
	}
}

void Warehouse::copyDynamic(const Warehouse& other)
{
	Device** tempDevices = new (std::nothrow) Device * [other.capacity];

	if (!tempDevices)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.size; i++)
		tempDevices[i] = other.devices[i] ? other.devices[i]->clone() : nullptr;

	for (size_t i = 0; i < size; i++)
		delete devices[i];

	delete[] devices;
	devices = tempDevices;
}

void Warehouse::freeDynamic()
{
	for (size_t i = 0; i < size; i++)
		delete devices[i];

	delete[] devices;
	devices = nullptr;
}

void Warehouse::resize()
{
	size_t tempCapacity = capacity * 2 + 1;
	Device** tempDevices = new (std::nothrow) Device * [tempCapacity];

	if (!tempDevices)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
		tempDevices[i] = devices[i] ? devices[i]->clone() : nullptr;

	for (size_t i = 0; i < size; i++)
		delete devices[i];

	delete[] devices;
	devices = tempDevices;
	capacity = tempCapacity;
}
