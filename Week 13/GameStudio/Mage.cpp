#include "Mage.h"
#include "Warrior.h"
#include "Necromancer.h"
#pragma warning (disable : 4996)

Mage::Mage() : Mage(0, "unknown", 0, 0, (int)Weapon::INVALID, 0) {}

Mage::Mage(int health, const char* name, int x, int y, int weapon, int attackDamage, const char* magic, double additionalDMG)
	: Player(health, name, x, y, weapon, attackDamage), magic(nullptr), additionalDMG(0)
{
	setAdditionalDMG(additionalDMG);
	setMagic(magic);
}

Mage::Mage(int health, const char* name, const Point& other, int weapon, int attackDamage, const char* magic, double additionalDMG)
	: Player(health, name, other, weapon, attackDamage), magic(nullptr), additionalDMG(0)
{
	setAdditionalDMG(additionalDMG);
	setMagic(magic);
}

Mage::Mage(const Player& other, const char* magic, double additionalDMG)
	: Player(other), magic(nullptr), additionalDMG(0)
{
	setAdditionalDMG(additionalDMG);
	setMagic(magic);
}

Mage::Mage(const Mage& other) : Player(other), additionalDMG(other.additionalDMG)
{
	copyDynamic(other);
}

Mage& Mage::operator=(const Mage& other)
{
	if (this != &other)
	{
		Player::operator=(other);
		additionalDMG = other.additionalDMG;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Mage::~Mage() noexcept
{
	freeDynamic();
}

void Mage::setMagic(const char* magic)
{
	if (!magic || strlen(magic) == 0)
		throw std::invalid_argument("Invalid magic\n");

	char* temp = new (std::nothrow) char[strlen(magic) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, magic);
	delete[] this->magic;
	this->magic = temp;
}

void Mage::setAdditionalDMG(double additionalDMG)
{
	const double EPS = 1e-9;
	if (additionalDMG <= EPS || additionalDMG >= 1.0 - EPS)
		throw std::out_of_range("additionalDMG must be between 0 and 1 (exclusive)");

	//if (additionalDMG <= 0.0 || additionalDMG >= 1.0)
	//	throw std::out_of_range("additionalDMG must be between 0 and 1 (exclusive)");

	this->additionalDMG = additionalDMG;
}

void Mage::attack(Player* enemy)
{
	if (!areNeighbors(this, enemy))
		throw std::logic_error("Players are not neighbors\n");

	double healthFromAdditionalDMG = static_cast<double>(enemy->getHealth() * additionalDMG);
	enemy->handleAttack(this);
}

void Mage::handleAttack(const Player* other)
{
	if (!areNeighbors(this, other))
		throw std::logic_error("Players are not neighbors\n");

	Player::handleAttack(other);
}

void Mage::print(std::ostream& os) const
{
	Player::print(os);

	if (!os.good())
		throw std::runtime_error("Can't work with stream\n");

	os << "Magic: " << magic << '\n'
		<< additionalDMG;
}

Player* Mage::clone() const
{
	return new Mage(*this);
}

void Mage::freeDynamic()
{
	delete[] magic;
	magic = nullptr;
}

void Mage::copyDynamic(const Mage& other)
{
	char* temp = new (std::nothrow) char[strlen(other.magic) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, other.magic);
	magic = temp;
}