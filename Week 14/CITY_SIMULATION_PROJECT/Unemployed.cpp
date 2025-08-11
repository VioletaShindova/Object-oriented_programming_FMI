#include "Unemployed.h"

Unemployed::Unemployed() : Profession() {}

Unemployed::Unemployed(const std::string& name, double salary) : Profession(name, salary) {}

Profession* Unemployed::clone() const
{
    return new Unemployed(*this);
}

bool Unemployed::isValidSalary(double salary) const
{
    return 0 <= salary;
}
