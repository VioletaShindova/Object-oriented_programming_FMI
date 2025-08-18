#include "Engineer.h"
#include "Corsair.h"
#pragma warning (disable : 4996)

Engineer::Engineer(): Engineer(0, "unknown", 0, 0, (int)Weapon::INVALID, 0) {}

Engineer::Engineer(int hull, const char* callsign, int x, int y, int weapon, int attackPower, const char* module, double coefficient)
	:Ship(hull, callsign, x, y, weapon, attackPower), module(nullptr), coefficient(0.1)
{
	setCoefficient(coefficient);
	setModule(module);
}

Engineer::Engineer(const Engineer& other) : Ship(other), coefficient(other.coefficient)
{
	copyDynamic(other);
}

Engineer& Engineer::operator=(const Engineer& other)
{
	if (this != &other)
	{
		Ship::operator=(other);
		coefficient= other.coefficient;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Engineer::~Engineer() noexcept
{
	freeDynamic();
}

void Engineer::setModule(const char* module) 
{
	if (!module || strlen(module) == 0)
		throw std::invalid_argument("Invalid module");

	char* temp = new (std::nothrow) char[strlen(module) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, module);
	delete[] this->module;
	this->module = temp;
}

void Engineer::setCoefficient(double coefficient)
{
	if (coefficient <= 0.0 || coefficient >= 1.0)
		throw std::invalid_argument("Coefficient must be in the range (0,1)\n");

	this->coefficient = coefficient;
}

void Engineer::attack(Ship* attacked)
{
	if (!attacked)
		throw std::invalid_argument("Invalid ship\n");

	if (!areNeighbors(this, attacked))
		throw std::runtime_error("Ships are not neighbors\n");

	attacked->setHull(attacked->getHull() * coefficient);
	attacked->handleFire(this);
}

void Engineer::handleFire(const Ship* other)
{
	if (!other)
		throw std::invalid_argument("Invalid ship\n");

	if (!areNeighbors(this, other))
		throw std::logic_error("Ships are not neighbors\n");

	Ship::handleFire(other);
}

void Engineer::print(std::ostream& os) const
{
	Ship::print(os);

	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	os << module << ' ' << coefficient << '\n';
}

Ship* Engineer::clone() const
{
	return new Engineer(*this);
}

void Engineer::freeDynamic()
{
	delete[] module;
	module = nullptr;
}

void Engineer::copyDynamic(const Engineer& other)
{
	char* temp = new (std::nothrow) char[strlen(other.module) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, other.module);
	module = temp;
}

bool operator==(const Engineer& lhs, const Engineer& rhs)
{
	return (static_cast<const Ship&>(lhs) == static_cast<const Ship&>(rhs)) &&
		strcmp(lhs.getModule(), rhs.getModule()) == 0;
}

bool operator!=(const Engineer& lhs, const Engineer& rhs)
{
	return !(lhs == rhs);
}
