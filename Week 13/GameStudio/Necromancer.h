#pragma once

#ifndef __NECROMANCER_HEADER_INCLUDED_

#define __NECROMANCER_HEADER_INCLUDED_

#include "Player.h"
#include "Mage.h"
#include "Point.h"
#include <iostream>

class Necromancer : public Mage
{
public:
	Necromancer();
	Necromancer(int health, const char* name, int x, int y, int weapon, int attackDamage, const char* magic = "unknown", double additionalDMG = 0);
	Necromancer(int health, const char* name, const Point& other, int weapon, int attackDamage, const char* magic = "unknown", double additionalDMG = 0);
	Necromancer(const Player& other, const char* magic = "unknown", double additionalDMG = 0);
	Necromancer(const Mage& other);
	Necromancer(const Necromancer& other);
	Necromancer& operator=(const Necromancer& other);
	~Necromancer() noexcept;

	inline Player** getBeatenPlayers() const { return beatenPlayers; }
	inline size_t getSize() const noexcept { return size; }

	virtual void attack(Player* enemy) override;

	virtual void handleAttack(const Player* other) override;

	virtual void print(std::ostream& os) const override;

	virtual Player* clone() const override;
private:
	void freeDynamic();
	void copyDynamic(const Necromancer& other);
	void resize();

	Player** beatenPlayers = {};
	size_t size = 0;
	size_t capacity = 1;
};

#endif