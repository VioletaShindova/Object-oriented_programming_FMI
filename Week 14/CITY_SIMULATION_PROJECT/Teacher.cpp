#include "Teacher.h"

Teacher::Teacher() : Profession() {}

Teacher::Teacher(const std::string& name, double salary) : Profession(name, salary) {}

Profession* Teacher::clone() const
{
    return new Teacher(*this);
}

bool Teacher::isValidSalary(double salary) const
{
    return (1200 <= salary) && (salary <= 1300);
}
