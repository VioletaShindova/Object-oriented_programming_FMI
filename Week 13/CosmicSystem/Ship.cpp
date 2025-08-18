#include "Ship.h"
#include <iostream>
#pragma warning (disable : 4996)

Ship::Ship() : Ship(0, "unknown", 0, 0, (int)Weapon::INVALID, 0) {}

Ship::Ship(int hull, const char* callsign, int x, int y, int weapon, int attackPower)
	: hull(0), callsign(nullptr), point(Point()), weapon(Weapon::INVALID), attack_Power(0)
{
	setHull(hull);
	setPoint(x, y);
	setWeapon(weapon);
	setAttackPower(attackPower);
	setCallSign(callsign);
}

Ship::Ship(const Ship& other) : hull(other.hull), point(other.point), weapon(other.weapon), attack_Power(other.attack_Power)
{
	copyDynamic(other);
}

Ship& Ship::operator=(const Ship& other)
{
	if (this != &other)
	{
		hull = other.hull; 
		point = other.point; 
		weapon = other.weapon; 
		attack_Power = other.attack_Power;

		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Ship::~Ship() noexcept
{
	freeDynamic();
}

void Ship::setHull(int hull)
{
	if (hull < 0)
		throw std::invalid_argument("Hull must be a positive number\n");

	this->hull = hull;
}

void Ship::setPoint(int x, int y)
{
	point = Point(x, y);
}

void Ship::setWeapon(int weapon)
{
	if(weapon < -1 || weapon > 4)
		throw std::invalid_argument("Weapon must be a number between 0 and 4\n");

	this->weapon = (Weapon)weapon;
}

void Ship::setAttackPower(int attackPower)
{
	if(attackPower < 0)
		throw std::invalid_argument("Attack power must be a positive number\n");

	attack_Power = attackPower;
}

unsigned Ship::getAttackPower() const
{
	return attack_Power;
}

void Ship::move(const Point& newPoint)
{
	setPoint(newPoint);
}

void Ship::handleFire(const Ship* other)
{
	if (!other)
		throw std::invalid_argument("Invalid ship\n");

	if (!areNeighbors(this, other))
		throw std::logic_error("Ships are not neighbors\n");

	if (!callsign || (0 < hull))
	{
		int res = hull - other->getAttackPower();

		if (0 < res)
		{
			hull = res;
			return;
		}
	}
	hull = 0;
}

void Ship::print(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	os << "Hull: " << hull << ' '
		<< "Callsign: " << callsign << ' '
		<< "Point: " << point << ' '
		<< "Weapon: " << (int)weapon << ' '
		<< "Attack power: " << attack_Power << ' ';
}

void Ship::setPoint(const Point& newPoint)
{
	point = newPoint;
}

void Ship::setCallSign(const char* callsign)
{
	if (!callsign || strlen(callsign) == 0)
		throw std::invalid_argument("Invalid callsign\n");

	char* temp = new (std::nothrow) char[strlen(callsign) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, callsign);
	delete[] this->callsign;
	this->callsign = temp;
}
void Ship::freeDynamic()
{
	delete[] callsign;
	callsign = nullptr;
}

void Ship::copyDynamic(const Ship& other)
{
	char* temp = new (std::nothrow) char[strlen(other.callsign) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, other.callsign);
	callsign = temp; //we accept that the current callsign either doesn't exist or it is already deleted
}

bool areNeighbors(const Ship* lhs, const Ship* rhs)
{
	return abs(lhs->getPoint().getX() - rhs->getPoint().getX()) == 1 ||
		   abs(lhs->getPoint().getY() - rhs->getPoint().getY()) == 1;
}

unsigned hull; //корпус/здравина
char* callsign; //позивна
Point point;
Weapon weapon;
unsigned attack_Power;

bool operator==(const Ship& lhs, const Ship& rhs)
{
	return lhs.getHull() == rhs.getHull() &&
		strcmp(lhs.getCallsign(), rhs.getCallsign()) == 0 &&
		lhs.getPoint() == rhs.getPoint() &&
		(int)lhs.getWeapon() == (int)rhs.getWeapon() &&
		lhs.getAttackPower() == rhs.getAttackPower();
}

bool operator!=(const Ship& lhs, const Ship& rhs)
{
	return !(lhs == rhs);
}
