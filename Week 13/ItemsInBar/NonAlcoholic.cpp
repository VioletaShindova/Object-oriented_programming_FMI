#include "NonAlcoholic.h"

NonAlcoholic::NonAlcoholic() : Drink() {}

NonAlcoholic::NonAlcoholic(const char* name, int ml) : Drink(name, ml) {}

NonAlcoholic::NonAlcoholic(const Drink& other) : Drink(other) {}

Drink* NonAlcoholic::clone() const
{
    return new NonAlcoholic(*this);
}

bool operator==(const NonAlcoholic& lhs, const NonAlcoholic& rhs)
{
    return static_cast<const Drink&>(lhs) == static_cast<const Drink&>(rhs);
}

bool operator!=(const NonAlcoholic& lhs, const NonAlcoholic& rhs)
{
    return !(lhs == rhs);
}
