#pragma once

#ifndef __ENGINEER_HEADER_INCLUDED_

#define __ENGINEER_HEADER_INCLUDED_

#include "Ship.h"
#include <iostream>

class Engineer : public Ship
{
public:
	Engineer();
	Engineer(int hull, const char* callsign, int x, int y, int weapon, int attackPower, const char* module = "unknown", double coefficient = 0.1);
	Engineer(const Engineer& other);
	Engineer& operator=(const Engineer& other);
	virtual ~Engineer() noexcept override;
	
	void setModule(const char* module);
	void setCoefficient(double coefficient);

	inline const char* getModule() const noexcept { return module; }
	inline double getCoefficient() const noexcept { return coefficient; }

	virtual void attack(Ship* attacked);

	virtual void handleFire(const Ship* other) override;

	virtual void print(std::ostream& os) const override;

	virtual Ship* clone() const override;

private:
	void freeDynamic();
	void copyDynamic(const Engineer& other);

	char* module;
	double coefficient;
};

bool operator==(const Engineer& lhs, const Engineer& rhs);
bool operator!=(const Engineer& lhs, const Engineer& rhs);

#endif