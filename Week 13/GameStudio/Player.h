#pragma once

#ifndef __PLAYER_HEADER_INCLUDED_

#define __PLAYER_HEADER_INCLUDED_

#include "Point.h"
#include <iostream>

enum class Weapon {
	INVALID = -1, 
	SWORD, 
	WAND, 
	STAFF, 
	AXE,
	COUNT
};

class Player
{
public:
	Player();
	Player(int health, const char* name, int x, int y, int weapon, int attackDamage);
	Player(int health, const char* name, const Point& other, int weapon, int attackDamage);
	Player(const Player& other);
	Player& operator=(const Player& other);
	virtual ~Player() noexcept;

	void setHealth(int health);
	void setPosition(int x, int y);
	void setPosition(const Point& other);
	void setWeapon(int weapon);
	void setWeapon(Weapon weapon);
	void setAttackDamage(int attackDamage);

	inline unsigned getHealth() const noexcept { return health; }
	inline const char* getName() const noexcept { return name; }
	inline const Point& getPosition() const noexcept { return position; }
	inline Weapon getWeapon() const noexcept { return weapon; }
	inline unsigned getAttackPower() const noexcept { return attack_damage; };
	
	void move(const Point& newPosition);
	void move(int x, int y);

	virtual void handleAttack(const Player* attacker);

	virtual void print(std::ostream& os) const;

	virtual Player* clone() const = 0;

protected:
	unsigned health;
	unsigned attack_damage;

private:
	void setName(const char* name);
	void freeDynamic();
	void copyDynamic(const Player& other);


	char* name;
	Point position;
	Weapon weapon;
};

bool areNeighbors(const Player* lhs, const Player* rhs);

#endif