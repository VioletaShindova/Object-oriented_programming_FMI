#pragma once

#ifndef __DRINK_HEADER_INCLUDED

#define __DRINK_HEADER_INCLUDED

#include <iostream>

class Drink
{
public:
	Drink();
	Drink(const char* name, int ml);
	Drink(const Drink& other);
	Drink& operator=(const Drink& other);
	virtual ~Drink() noexcept;

	virtual Drink* clone() const = 0;

	void setName(const char* name);
	void setML(int ml);
	void setCounOfEachDrink(int count);

	inline const char* getName() const noexcept { return name; }
	inline unsigned getML() const noexcept { return ml; }
	inline unsigned getCountOfEachDrink() const noexcept { return countOfEachDrink; }

	friend bool operator==(const Drink& lhs, const Drink& rhs);
	friend bool operator!=(const Drink& lhs, const Drink& rhs);
private:
	void freeDynamic();
	void copyDynamic(const Drink& other);

	char* name;
	unsigned ml;
	unsigned countOfEachDrink = 0;
};

#endif