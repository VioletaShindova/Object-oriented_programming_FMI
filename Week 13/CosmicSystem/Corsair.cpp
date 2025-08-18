#include "Corsair.h"
#include "Ship.h"
#include <ctime>
#include "FleetCollection.h"

Corsair::Corsair() : Corsair(0, "unknown", 0, 0, (int)Weapon::INVALID, 0) {}

Corsair::Corsair(int hull, const char* callsign, int x, int y, int weapon, int attackPower, const char* module, double coefficient, int capacity)
	: Engineer(hull, callsign, x, y, weapon, attackPower, module, coefficient), beatenShips(nullptr), size(0), capacity(1)
{
	setCapacity(capacity);
}

Corsair::Corsair(const Corsair& other) : Engineer(other), size(other.size), capacity(other.capacity)
{
	copyDynamic(other);
}

Corsair& Corsair::operator=(const Corsair& other)
{
	if (this != &other)
	{
		Engineer::operator=(other);
		size = other.size; 
		capacity = other.capacity;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Corsair::~Corsair() noexcept
{
	freeDynamic();
}

void Corsair::attack(Ship* attacked)
{
	if (!attacked)
		throw std::invalid_argument("Invalid ship\n");

	if (!areNeighbors(this, attacked))
		throw std::logic_error("Ships are not neighbors\n");

	attacked->handleFire(this);
	if (attacked->getHull() == 0)
	{
		attacked->handleFire(beatenShips[rand() % size]);

		if (size + 1 >= capacity)
			resize();

		beatenShips[size++] = attacked->clone();
	}
}

void Corsair::handleFire(const Ship* other)
{
	if (!other)
		throw std::invalid_argument("Invalid ship\n");

	if (!areNeighbors(this, other))
		throw std::logic_error("Ships are not neighbors\n");

	Engineer::handleFire(other);
}

void Corsair::print(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	for (size_t i = 0; i < size; i++)
	{
		if(beatenShips[i])
			beatenShips[i]->print(os);
	}
	os << '\n';
}

Ship* Corsair::clone() const
{
	return new Corsair(*this);
}

void Corsair::setCapacity(int capacity)
{
	if (capacity < 0 || capacity < size)
		throw std::invalid_argument("Invalid capacity\n");

	Ship** temp = new (std::nothrow) Ship * [capacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
		temp[i] = beatenShips[i] ? beatenShips[i]->clone() : nullptr;

	for (size_t i = 0; i < size; i++)
		delete beatenShips[i];
	delete[] beatenShips;
	beatenShips = temp;
}

void Corsair::freeDynamic()
{
	for (size_t i = 0; i < size; i++)
		delete beatenShips[i];

	delete[] beatenShips;
	beatenShips = nullptr;
}

void Corsair::copyDynamic(const Corsair& other)
{
	Ship** temp = new (std::nothrow) Ship * [other.capacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.size; i++)
		temp[i] = other.beatenShips[i] ? other.beatenShips[i]->clone() : nullptr;

	beatenShips = temp;
}

void Corsair::resize()
{
	size_t tempCapacity = capacity * 2 + 1;

	Ship** temp = new (std::nothrow) Ship * [tempCapacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
		temp[i] = beatenShips[i];

	delete[] beatenShips;
	beatenShips = temp;
	capacity = tempCapacity;
}

bool operator==(const Corsair& lhs, const Corsair& rhs)
{
	for (size_t i = 0; i < lhs.getSize(); i++) {
		if (*(lhs.getShips()[i]) != *(rhs.getShips()[i]))
			return false;
	}

	return (static_cast<const Ship&>(lhs) == static_cast<const Ship&>(rhs)) && 
		lhs.getSize() == rhs.getSize();
}

bool operator!=(const Corsair& lhs, const Corsair& rhs)
{
	return !(lhs == rhs);
}
