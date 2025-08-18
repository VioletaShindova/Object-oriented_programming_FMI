#pragma once

#ifndef __SHIP_HEADER_INCLUDED_

#define __SHIP_HEADER_INCLUDED_

#include "Point.h"
#include <iostream>

enum class Weapon {
	INVALID = -1,
	LASER, 
	RAILGUN, 
	PLASMA, 
	MISSILE,
	COUNT
};

class Ship
{
public:
	Ship();
	Ship(int hull, const char* callsign, int x, int y, int weapon, int attackPower);
	Ship(const Ship& other);
	Ship& operator=(const Ship& other);
	virtual ~Ship() noexcept;

	void setHull(int hull);
	void setPoint(int x, int y);
	void setWeapon(int weapon);
	void setAttackPower(int attackPower);

	inline unsigned getHull() const noexcept { return hull; }
	inline const char* getCallsign() const noexcept { return callsign; }
	inline const Point& getPoint() const noexcept { return point; }
	inline Weapon getWeapon() const noexcept { return weapon; }

	void move(const Point& newPoint);

	unsigned getAttackPower() const;

	virtual void handleFire(const Ship* other);

	virtual void print(std::ostream& os) const;

	virtual Ship* clone() const = 0;

private:
	void setPoint(const Point& newPoint);
	void setCallSign(const char* callsign);
	void freeDynamic();
	void copyDynamic(const Ship& other);

	unsigned hull; //корпус/здравина
	char* callsign; //позивна
	Point point;
	Weapon weapon;
	unsigned attack_Power;
};

bool areNeighbors(const Ship* lhs, const Ship* rhs);

bool operator==(const Ship& lhs, const Ship& rhs);
bool operator!=(const Ship& lhs, const Ship& rhs);

#endif