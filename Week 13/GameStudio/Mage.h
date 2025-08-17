#pragma once

#ifndef __MAGE_HEADER_INCLUDED_

#define __MAGE_HEADER_INCLUDED_

#include "Player.h"
#include "Point.h"
#include <iostream>

class Mage : public Player
{
public:
	Mage();
	Mage(int health, const char* name, int x, int y, int weapon, int attackDamage, const char* magic = "unknown", double additionalDMG = 0);
	Mage(int health, const char* name, const Point& other, int weapon, int attackDamage, const char* magic = "unknown", double additionalDMG = 0);
	Mage(const Player& other, const char* magic = "unknown", double additionalDMG = 0);
	Mage(const Mage& other);
	Mage& operator=(const Mage& other);
	~Mage() noexcept;

	void setMagic(const char* magic);
	void setAdditionalDMG(double additionalDMG);

	inline const char* getMagic() const noexcept { return magic; }
	inline double getAdditionalDMG() const noexcept { return additionalDMG; }

	virtual void attack(Player* enemy);

	virtual void handleAttack(const Player* other) override;

	virtual void print(std::ostream& os) const override;

	virtual Player* clone() const override;
private:
	void freeDynamic();
	void copyDynamic(const Mage& other);

	char* magic;
	double additionalDMG;
};

#endif