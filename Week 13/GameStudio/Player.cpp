#include "Player.h"
#include <cmath>
#include "Mage.h"
#pragma warning (disable : 4996)

Player::Player() : Player(0, "unknown", 0, 0, (int)Weapon::INVALID, 0) {}

Player::Player(int health, const char* name, int x, int y, int weapon, int attackDamage)
	: health(0), name(nullptr), position(Point()), weapon(Weapon::INVALID), attack_damage(0)
{
	setHealth(health);
	setPosition(x,y);
	setWeapon(weapon);
	setAttackDamage(attackDamage);
	setName(name);
}
Player::Player(int health, const char* name, const Point& other, int weapon, int attackDamage)
{
	setHealth(health);
	setPosition(other);
	setWeapon(weapon);
	setAttackDamage(attackDamage);
	setName(name);
}

Player::Player(const Player& other) 
	: health(other.health), position(other.position), weapon(other.weapon), attack_damage(other.attack_damage)
{
	copyDynamic(other);
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		health = other.health;
		position = other.position;
		weapon = other.weapon;
		attack_damage = other.attack_damage;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Player::~Player() noexcept
{
	freeDynamic();
}

void Player::setHealth(int health)
{
	if (health < 0)
		throw std::invalid_argument("Health must be a positive number\n");

	this->health = health;
}

void Player::setPosition(int x, int y)
{
	position = Point(x, y);
}

void Player::setPosition(const Point& other)
{
	position = other;
}

void Player::setWeapon(int weapon)
{
	if (weapon < (int)Weapon::INVALID || weapon >= (int)Weapon::COUNT)
		throw std::invalid_argument("Weapon must be a number between 0 and 4\n");

	this->weapon = (Weapon)weapon;
}

void Player::setWeapon(Weapon weapon)
{
	this->weapon = weapon;
}

void Player::setAttackDamage(int attackDamage)
{
	if (attackDamage < 0)
		throw std::invalid_argument("Attack damage must be a positive number\n");

	attack_damage = attackDamage;
}

void Player::move(const Point& newPosition)
{
	setPosition(newPosition);
}

void Player::move(int x, int y)
{
	setPosition(x, y);
}

void Player::handleAttack(const Player* attacker)
{
	if (areNeighbors(this, attacker))
	{
		if (health - attacker->getAttackPower() <= 0)
		{
			health = 0;
			attack_damage = 0; //must die but instead he will deal 0 damage
		}
		else
			health -= attacker->getAttackPower();
	}
	else
		throw std::logic_error("Players are not neighbors\n");
}

void Player::print(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	os << "Health: " << health << '\n'
		<< "Name: " << name << '\n'
		<< "Position" << position << '\n'
		<< "Weapon:" << (int)weapon << '\n'
		<< "Attack damage: " << attack_damage;
}

void Player::setName(const char* name)
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

void Player::freeDynamic()
{
	delete[] name;
	name = nullptr;
}

void Player::copyDynamic(const Player& other)
{
	char* temp = new (std::nothrow) char[strlen(other.name) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, other.name);
	name = temp; //we accept that name has already been deleted
}

bool areNeighbors(const Player* lhs, const Player* rhs)
{
	return (abs(lhs->getPosition().getX() - rhs->getPosition().getX()) == 1 || 
			abs(lhs->getPosition().getY() - rhs->getPosition().getY()) == 1);
}
