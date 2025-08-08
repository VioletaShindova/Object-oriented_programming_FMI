#pragma once

#ifndef __ELECTRICAL_APPLIANCE_HEADER_INCLUDED_

#define __ELECTRICAL_APPLIANCE_HEADER_INCLUDED_

#include <iostream>

class ElectricalAppliance
{
public:
	ElectricalAppliance();
	ElectricalAppliance(const char* description, const char* brand, double power, bool status = false, bool active = false);
	ElectricalAppliance(const ElectricalAppliance& other);
	ElectricalAppliance& operator=(const ElectricalAppliance& other);
	~ElectricalAppliance() noexcept;

	void setDescription(const char* description);
	void setBrand(const char* brand);
	void setPower(double power);
	void setStatus(bool status);
	void setActive(bool active);

	inline const char* getDescription() const noexcept { return description; }
	inline const char* getBrand() const noexcept { return brand; }
	inline double getPower() const noexcept { return power; }
	inline bool getStatus() const noexcept { return status; }
	inline bool getActive() const noexcept { return active; }
	inline unsigned getID() const noexcept { return id; }

	void writeToStream(std::ostream& os);
	void readFromStream(std::istream& is);

private:
	static unsigned incrementID();

	void copyDynamic(const ElectricalAppliance& other);
	void freeDynamic();

	char* description;
	char* brand;
	double power; //положително реално число
	bool status; //plugged in or not). При включване се указва къде е включен;
	bool active;

	unsigned id;
	static unsigned currID; //Той трябва да е уникален за всеки уред и след
							//създаване не се променя, дори при присвояване.
};

bool areEqual(const ElectricalAppliance* lhs, const ElectricalAppliance* rhs);

#endif