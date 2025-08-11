#include "Programmer.h"

Programmer::Programmer() : Profession() {}

Programmer::Programmer(const std::string& name, double salary) : Profession(name, salary) {}

Profession* Programmer::clone() const
{
    return new Programmer(*this);
}

bool Programmer::isValidSalary(double salary) const
{
    return (2000 <= salary) && (salary <= 5000);
}
