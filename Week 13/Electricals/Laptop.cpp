#include "Laptop.hpp"
#include <iostream>

Laptop::Laptop() : Laptop(0, 0){}

Laptop::Laptop(int ram, int ssd) 
    : Device()
{
    setRAM(ram);
    setSSD(ssd);
}

Laptop::Laptop(const char* name, const char* producer, double power, bool status, int ram, int ssd)
    : Device(name, producer, power, status), ram(0), ssd(0)
{
    setRAM(ram);
    setSSD(ssd);
}

Laptop::Laptop(const Device& other, int ram, int ssd) 
    : Device(other), ram(0), ssd(0)
{
    setRAM(ram);
    setSSD(ssd);
}

void Laptop::setRAM(int ram)
{
    if (ram < 0)
        throw std::invalid_argument("RAM must be a positive number\n");

    this->ram = ram;
}

void Laptop::setSSD(int ssd)
{
    if (ssd < 0)
        throw std::invalid_argument("SSD must be a positive number\n");

    this->ssd = ssd;
}

Device* Laptop::clone() const
{
    return new Laptop(*this);
}

double Laptop::getPrice() const
{
    return (power*2) +(ram*15) + (ssd * 0.1);
}

void Laptop::print(std::ostream& os) const
{
    Device::print(os);

    if (!os.good())
        throw std::runtime_error("Can't open stream\n");

    os << ',' << ram << ',' << ssd << '\n';
}
