#include "Device.hpp"
#include <iostream>

#pragma once

#ifndef __SMART_TV_HEADER_INCLUDED_

#define __SMART_TV_HEADER_INCLUDED_

class SmartTV : public Device
{
public:
	SmartTV();
	SmartTV(const char* resolution, int inches);
	SmartTV(const char* name, const char* producer, double power = 0, bool status = false, const char* resolution = "unknown", int inches = 0);
	SmartTV(const Device& other, const char* resolution = "unknown", int inches = 0);
	SmartTV(const SmartTV& other);
	SmartTV& operator=(const SmartTV& other);
	~SmartTV() noexcept;

	inline const char* getResolution() const noexcept { return resolution; }
	inline unsigned getInches() const noexcept { return inches; }

	void setResolution(const char* resolution);
	void setInches(int inches);

	Device* clone() const override;
	double getPrice() const override;
	void print(std::ostream& os) const override;

private:
	void freeDynamic();
	void copyDynamic(const SmartTV& other);

	char* resolution;
	unsigned inches;
};

#endif