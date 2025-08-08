#pragma once

#ifndef __POWER_STRING_HEADER_INCLUDED_

#define __POWER_STRING_HEADER_INCLUDED_

#include <iostream>

class ElectricalAppliance;

class PowerString
{
public:
	PowerString();
	explicit PowerString(int countNest);
	PowerString(int countNest, int maxPower);
	PowerString(const PowerString& other);
	PowerString& operator=(const PowerString& other) = delete;
	~PowerString();

	void turnOnDevice(const ElectricalAppliance* device);
	void turnOffDevice(const ElectricalAppliance* device);

	void writeToStream(std::ostream& os); //броя гнезда, максимално допустимия ток, текущо използвания ток и информация за всички включени
										  //в разклонителя уреди;

	inline const ElectricalAppliance** getElectricalAppliances() const noexcept { return electricals; }
	inline size_t getCountNest() const noexcept { return countNest; }
	inline double getMaxPower() const noexcept { return maxPower; }

private:
	void freeDynamic();
	void copyDynamic(const PowerString& other);

	void setNests(int countNest);
	void setMaxPower(int maxPower);

	ElectricalAppliance** electricals;
	double currentUsedElectric = 0;
	size_t currentElectricals;
	size_t countNest; //подава се при създаване на обекта и след това е непроменим;

	double maxPower; //максимално възможния общ ток от всички включени (turned on) в разклонителя уреди.

};

#endif