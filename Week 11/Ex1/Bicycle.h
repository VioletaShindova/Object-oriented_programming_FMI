#pragma once
#include "Vehicle.h"

class Bicycle : public Vehicle {
public:
	Bicycle();
	Bicycle(int number_Of_Gears, bool _hasLights, bool _hasHorn);
	Bicycle(Color color, const char* brand,
		int year_Of_Manufacture,
		int passengers_Capacity,
		int maximum_Speed_Capacity, int number_Of_Gears, bool _hasLights, bool _hasHorn);
	Bicycle(const Vehicle& other);
	Bicycle(const Vehicle& other, int number_Of_Gears, bool _hasLights, bool _hasHorn);

	inline size_t getNumberOfGears() const noexcept { return _number_Of_Gears; }

	inline bool getHasLights() const noexcept { return _hasLights; }

	inline bool getHasHorn() const noexcept { return _hasHorn; }

private:
	void setNumberOfGears(int number_Of_Gears);
	size_t _number_Of_Gears;
	bool _hasLights;
	bool _hasHorn;
};

