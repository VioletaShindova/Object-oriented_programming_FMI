#include "Alcoholic.hpp"

Alcoholic::Alcoholic() : Alcoholic(0) {}

Alcoholic::Alcoholic(int proMille) 
    : Drink(), proMille(0)
{
    setProMille(proMille);
}

Alcoholic::Alcoholic(const char* name, int ml, int proMille)
    : Drink(name, ml), proMille(0)
{
    setProMille(proMille);
}

Alcoholic::Alcoholic(const Drink& other, int proMille)
    : Drink(other), proMille(0)
{
    setProMille(proMille);
}

Drink* Alcoholic::clone() const
{
    return new Alcoholic(*this);
}

void Alcoholic::setProMille(int proMille)
{
    if (proMille < 0)
        throw std::invalid_argument("Pro mille must be a positive number\n");

    this->proMille = proMille;
}

bool operator==(const Alcoholic& lhs, const Alcoholic& rhs)
{
    return static_cast<const Drink&>(lhs) == static_cast<const Drink&>(rhs) && 
        lhs.proMille == rhs.proMille;
}

bool operator!=(const Alcoholic& lhs, const Alcoholic& rhs)
{
    return !(lhs == rhs);
}
