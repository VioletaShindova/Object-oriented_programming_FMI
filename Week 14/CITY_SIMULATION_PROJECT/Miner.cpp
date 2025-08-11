#include "Miner.h"

Miner::Miner() : Profession() {}

Miner::Miner(const std::string& name, double salary) :Profession(name, salary) {}

Profession* Miner::clone() const
{
    return new Miner(*this);
}

bool Miner::isValidSalary(double salary) const
{
    return (1000 <= salary) && (salary <= 3000);
}
