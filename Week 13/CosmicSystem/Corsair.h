#pragma once

#ifndef __CORSAIR_HEADER_INCLUDED_

#define __CORSAIR_HEADER_INCLUDED_

#include "Engineer.h"
#include <iostream>

class Ship;

class Corsair : public Engineer
{
public:
	Corsair();
	Corsair(int hull, const char* callsign, int x, int y, int weapon, int attackPower, const char* module = "unknown", double coefficient = 0.1, int capacity = 1);
	Corsair(const Corsair& other);
	Corsair& operator=(const Corsair& other);
	virtual ~Corsair() noexcept override;

	inline Ship** getShips() const noexcept { return beatenShips; }
	inline size_t getSize() const noexcept { return size; }

	virtual void attack(Ship* attacked);

	virtual void handleFire(const Ship* other) override;

	virtual void print(std::ostream& os) const override;

	virtual Ship* clone() const override;
private:
	void setCapacity(int capacity);
	void freeDynamic();
	void copyDynamic(const Corsair& other);
	void resize();

	Ship** beatenShips;
	size_t size;
	size_t capacity;
};

bool operator==(const Corsair& lhs, const Corsair& rhs);
bool operator!=(const Corsair& lhs, const Corsair& rhs);

#endif