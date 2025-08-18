#include "FleetCollection.h"
#include "Ship.h"
#include <iostream>

FleetCollection::FleetCollection() : FleetCollection(1) {}

FleetCollection::FleetCollection(int capacity)
	: ships(nullptr), size(0), capacity(1)
{
	setCapacity(capacity);
}

FleetCollection::FleetCollection(const FleetCollection& other) :size(other.size), capacity(other.capacity)
{
	copyDynamic(other);
}

FleetCollection& FleetCollection::operator=(const FleetCollection& other)
{
	if (this != &other)
	{
		size = other.size;
		capacity = other.capacity;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

FleetCollection::~FleetCollection() noexcept
{
	freeDynamic();
}

bool FleetCollection::addShip(const Ship* toAddShip)
{
	if (!toAddShip)
		throw std::invalid_argument("Invalid ship\n");

	if (isFound(toAddShip))
		return false;

	if (size + 1 >= capacity)
		resize();

	ships[size++] = toAddShip->clone();
	return true;
}

bool FleetCollection::removeShip(const Ship* toRemoveShip)
{
	if (!toRemoveShip)
		throw std::invalid_argument("Invalid ship\n");

	if (size == 0)
		throw std::logic_error("There are no ships to remove");

	for (size_t i = 0; i < size; i++)
	{
		if (*ships[i] == *toRemoveShip) //careful if it is Ship* or Ship&
		{
			std::swap(ships[i], ships[size - 1]);
			delete ships[size - 1];
			ships[size - 1] = nullptr;
			size--;
			return true;
		}
	}
	return false;
}

const Ship* FleetCollection::operator[](int index) const
{
	if (index < 0 || index >= size)
		throw std::invalid_argument("Invalid index\n");

	return ships[index];
}

bool FleetCollection::isFound(const Ship* toFind) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (*ships[i] == *toFind)
			return true;
	}
	return false;
}

void FleetCollection::setCapacity(int capacity)
{
	if (capacity < 0 || capacity < size)
		throw std::invalid_argument("Invalid capacity\n");

	Ship** temp = new (std::nothrow) Ship * [capacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
		temp[i] = ships[i] ? ships[i]->clone() : nullptr;

	for (size_t i = 0; i < size; i++)
		delete ships[i];

	delete[] ships;
	ships = temp;
	this->capacity = capacity;
}

void FleetCollection::freeDynamic()
{
	for (size_t i = 0; i < size; i++)
	{
		delete ships[i];
	}
	delete[] ships;
	ships = nullptr;
}

void FleetCollection::copyDynamic(const FleetCollection& other)
{
	Ship** temp = new (std::nothrow) Ship * [other.capacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();;

	for (size_t i = 0; i < other.size; i++)
		temp[i] = other.ships[i] ? other.ships[i]->clone() : nullptr;

	ships = temp;
}

void FleetCollection::resize()
{
	size_t tempCapacity = capacity * 2 + 1;
	Ship** temp = new (std::nothrow) Ship * [tempCapacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();;

	for (size_t i = 0; i < size; i++)
		temp[i] = ships[i];

	delete[] ships;
	ships = temp;
	capacity = tempCapacity;
}