#include "Fighter.h"

Fighter::Fighter() : Fighter(0, "unknown", 0, 0, (int)Weapon::INVALID, 0) {}

Fighter::Fighter(int hull, const char* callsign, int x, int y, int weapon, int attackPower, int shield)
	:Ship(hull, callsign, x,y,weapon, attackPower), shield(0)
{
	setShield(shield);
}

void Fighter::setShield(int shield)
{
	if (shield < 0)
		throw std::invalid_argument("Invalid shield\n");

	this->shield = shield;
}

void Fighter::handleFire(const Ship* other)
{
	if (!other)
		throw std::invalid_argument("Invalid ship\n");

	if (!areNeighbors(this, other))
		throw std::logic_error("The ships are not neighbors\n");

	if (0 < shield)
	{
		int res = shield - other->getAttackPower();

		if (res < 0)
		{
			shield = 0;
			Ship::handleFire(other);
		}

		shield = res;
	}
	Ship::handleFire(other);
}

void Fighter::print(std::ostream& os) const
{
	Ship::print(os);

	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	os << shield << '\n';
}

Ship* Fighter::clone() const
{
	return new Fighter(*this);
}

bool operator==(const Fighter& lhs, const Fighter& rhs)
{
	return (static_cast<const Ship&>(lhs) == static_cast<const Ship&>(rhs)) &&
		lhs.getShield() == rhs.getShield();
}

bool operator!=(const Fighter& lhs, const Fighter& rhs)
{
	return !(lhs == rhs);
}
