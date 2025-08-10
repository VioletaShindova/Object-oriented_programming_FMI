#include "Device.hpp"
#include <iostream>

#pragma once

#ifndef __LAPTOP_HEADER_INCLUDED_

#define __LAPTOP_HEADER_INCLUDED_

class Laptop : public Device
{
public:
	Laptop();
	Laptop(int ram, int ssd);
	Laptop(const char* name, const char* producer, double power = 0, bool status = false, int ram = 0, int ssd = 0);
	Laptop(const Device& other, int ram = 0, int ssd = 0);

	void setRAM(int ram);
	void setSSD(int ssd);

	inline unsigned getRAM() const noexcept { return ram; }
	inline unsigned getSSD() const noexcept { return ssd; }

	Device* clone() const override;

	double getPrice() const override;
	void print(std::ostream& os) const override;

private:
	unsigned ram;
	unsigned ssd;
};

#endif