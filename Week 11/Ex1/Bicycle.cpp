#include "Bicycle.h"

Bicycle::Bicycle() : Bicycle(GlobalConstants::MIN_SIZE_GEARS, false, false) {}

Bicycle::Bicycle(int number_Of_Gears, bool _hasLights, bool _hasHorn) 
	: Vehicle(), _hasLights(_hasHorn), _hasHorn(_hasHorn) {
	setNumberOfGears(number_Of_Gears);
}

Bicycle::Bicycle(Color color, const char* brand, int year_Of_Manufacture, int passengers_Capacity, int maximum_Speed_Capacity, int number_Of_Gears, bool _hasLights, bool _hasHorn) 
	: Vehicle(color, brand, year_Of_Manufacture, passengers_Capacity, maximum_Speed_Capacity), _hasLights(_hasLights), _hasHorn(_hasHorn) {
	setNumberOfGears(number_Of_Gears);
}

Bicycle::Bicycle(const Vehicle& other) : 
	Vehicle(other), _number_Of_Gears(GlobalConstants::MIN_SIZE_GEARS), _hasLights(false), _hasHorn(false) {}

Bicycle::Bicycle(const Vehicle& other, int number_Of_Gears, bool _hasLights, bool _hasHorn) : 
	Vehicle(other), _hasLights(_hasLights), _hasHorn(_hasHorn) {
	setNumberOfGears(number_Of_Gears);
}

void Bicycle::setNumberOfGears(int number_Of_Gears) {
	if (number_Of_Gears < 0)
		throw std::invalid_argument("Gears must be at least 0!");

	_number_Of_Gears = number_Of_Gears;
}
