#pragma once

#ifndef __NON_ALCOHOLIC_HEADER_INCLUDED

#define __NON_ALCOHOLIC_HEADER_INCLUDED

#include "Drink.hpp"

class NonAlcoholic : public Drink
{
public:
	NonAlcoholic();
	NonAlcoholic(const char* name, int ml);
	NonAlcoholic(const Drink& other);

	virtual Drink* clone() const override;

	friend bool operator==(const NonAlcoholic& lhs, const NonAlcoholic& rhs);
	friend bool operator!=(const NonAlcoholic& lhs, const NonAlcoholic& rhs);

private:
};

#endif