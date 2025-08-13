#pragma once

#ifndef __ALCOHOLIC_HEADER_INCLUDED

#define __ALCOHOLIC_HEADER_INCLUDED

#include "Drink.hpp"

class Alcoholic : public Drink
{
public:
	Alcoholic();
	Alcoholic(int proMille);
	Alcoholic(const char* name, int ml, int proMille = 0);
	Alcoholic(const Drink& other, int proMille = 0);

	virtual Drink* clone() const override;

	void setProMille(int proMille);

	friend bool operator==(const Alcoholic& lhs, const Alcoholic& rhs);
	friend bool operator!=(const Alcoholic& lhs, const Alcoholic& rhs);
private:
	unsigned proMille;
};

#endif // !__ALCOHOLIC_HEADER_INCLUDED