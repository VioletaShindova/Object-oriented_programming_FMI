#pragma once

#ifndef __FIGHTER_HEADER_INCLUDED_

#define __FIGHTER_HEADER_INCLUDED_

#include "Ship.h"
#include <iostream>

class Fighter : public Ship
{
public:
	Fighter();
	Fighter(int hull, const char* callsign, int x, int y, int weapon, int attackPower, int shield = 0);

	void setShield(int shield);

	inline unsigned getShield() const noexcept { return shield; }

	virtual void handleFire(const Ship* other) override;

	virtual void print(std::ostream& os) const override;

	virtual Ship* clone() const override;
private:
	unsigned shield;
};

bool operator==(const Fighter& lhs, const Fighter& rhs);
bool operator!=(const Fighter& lhs, const Fighter& rhs);

#endif