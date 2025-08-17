#pragma once

#ifndef __WARRIOR_HEADER_INCLUDED_

#define __WARRIOR_HEADER_INCLUDED_

#include "Player.h"
#include "Point.h"
#include <iostream>

class Warrior : public Player
{
public:
	Warrior();
	Warrior(int health, const char* name, int x, int y, int weapon, int attackDamage,int shield = 0);
	Warrior(int health, const char* name, const Point& other, int weapon, int attackDamage, int shield = 0);
	Warrior(const Player& other, int shield = 0);

	void setShield(int shield);

	inline unsigned getShield() const noexcept { return shield; }

	virtual void handleAttack(const Player* other) override;

	virtual void print(std::ostream& os) const override;

	virtual Player* clone() const override;
private:
	unsigned shield; //must be unsigned
};

#endif