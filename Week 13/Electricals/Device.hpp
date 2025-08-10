#include <iostream>

#pragma once

#ifndef __DEVICE_HEADER_INCLUDED_

#define __DEVICE_HEADER_INCLUDED_

class Device
{
public:
	Device();
	Device(const char* name, const char* producer, double power = 0, bool status = false);
	Device(const Device& other);
	Device& operator=(const Device& other);
	virtual ~Device() noexcept; //virtual becuase that way the right dtors will be called

	virtual Device* clone() const = 0;

	void setName(const char* name);
	void setProducer(const char* producer);
	void setPower(double power);
	void setStatus(bool status);

	inline const char* getName() const noexcept { return name; }
	inline const char* getProducer() const noexcept { return producer; }
	inline double getPower() const noexcept { return power; }
	inline bool getStatus() const noexcept { return status; }

	virtual double getPrice() const = 0;
	virtual void print(std::ostream& os) const;

protected:
	double power;

private:
	void freeDynamic();
	void copyDynamic(const Device& other);

	char* name;
	char* producer;
	bool status; //turned on/off
};

#endif