#include "Car.h"

Car::Car() : Car("unknown", GlobalConstants::MIN_DOORS_COUNT, GlobalConstants::MIN_CAR_HORSEPOWER) {}

Car::Car(const std::string model, int count_Of_Doors, int engine_HorsePower) 
	: Vehicle(), _model(model) 
{
	setDoorsCount(count_Of_Doors);
	setEngineHorsePower(engine_HorsePower);
}

Car::Car(Color color, const char* brand, int year_Of_Manufacture,
	int passengers_Capacity, int maximum_Speed_Capacity,
	const std::string model, int count_Of_Doors,
	int engine_HorsePower)
	: Vehicle(color, brand, year_Of_Manufacture, passengers_Capacity, maximum_Speed_Capacity), _model(model) 
{
	setDoorsCount(count_Of_Doors);
	setEngineHorsePower(engine_HorsePower);
}

Car::Car(const Vehicle& other, const std::string model, int count_Of_Doors, int engine_HorsePower)
	: Vehicle(other), _model(model) 
{
	setDoorsCount(count_Of_Doors);
	setEngineHorsePower(engine_HorsePower);
}

void Car::setDoorsCount(int count_Of_Doors) {
	if (count_Of_Doors < GlobalConstants::MIN_DOORS_COUNT)
		throw std::invalid_argument("Doors count must be at least " + GlobalConstants::MIN_DOORS_COUNT + '!');

	_count_Of_Doors = count_Of_Doors;
}

void Car::setEngineHorsePower(int engine_HorsePower) {
	if (engine_HorsePower < GlobalConstants::MIN_CAR_HORSEPOWER)
		throw std::invalid_argument("Doors count must be at least " + GlobalConstants::MIN_CAR_HORSEPOWER + '!');

	_engine_HorsePower = engine_HorsePower;
}