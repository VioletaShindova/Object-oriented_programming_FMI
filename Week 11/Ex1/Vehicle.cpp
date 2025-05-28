#include "Vehicle.h"

Vehicle::Vehicle() : Vehicle(Color::INVALID, "unknown", GlobalConstants::YEAR_OF_MANUFACTURE, GlobalConstants::MIN_PASSENGERS_CAPACITY, GlobalConstants::MIN_SPEED_CAPACITY) {}

Vehicle::Vehicle(Color color, const char* brand, int year_Of_Manufacture, int passengers_Capacity, int maximum_Speed_Capacity) 
	: _color(color) {
	setYearOfManufacture(year_Of_Manufacture);
	setCapacityOfPassengers(passengers_Capacity);
	setSpeedCapacity(maximum_Speed_Capacity);
	setBrand(brand);
}

Vehicle::Vehicle(const Vehicle& other) 
	: _color(other._color), _year_Of_Manufacture(other._year_Of_Manufacture), 
	  _passengers_Capacity(other._passengers_Capacity), _maximum_Speed_Capacity(other._maximum_Speed_Capacity) {
	copyDynamic(other);
}

Vehicle& Vehicle::operator=(const Vehicle& other) {
	if (this != &other) {
		freeDynamic();
		copyDynamic(other);

		_color = other._color;
		_year_Of_Manufacture = other._year_Of_Manufacture;
		_passengers_Capacity = other._passengers_Capacity;
		_maximum_Speed_Capacity = other._maximum_Speed_Capacity;
	}
	return *this;
}

Vehicle::~Vehicle() noexcept {
	freeDynamic();
}

void Vehicle::copyDynamic(const Vehicle& other) {
	_brand = new (std::nothrow) char[strlen(other._brand) + 1];

	if (!_brand)
		throw std::bad_alloc();

	strcpy(_brand, other._brand);
}

void Vehicle::freeDynamic() noexcept {
	delete[] _brand;
	_brand = nullptr;
}

void Vehicle::setYearOfManufacture(int year_Of_Manufacture) {
	if (year_Of_Manufacture < GlobalConstants::YEAR_OF_MANUFACTURE)
		throw std::invalid_argument("The year of manufacture must be at least " + GlobalConstants::YEAR_OF_MANUFACTURE + '!');

	_year_Of_Manufacture = year_Of_Manufacture;
}

void Vehicle::setCapacityOfPassengers(int passengers_Capacity) {
	if (passengers_Capacity < GlobalConstants::MIN_PASSENGERS_CAPACITY)
		throw std::invalid_argument("The min capacity of passengers must be at least " + GlobalConstants::MIN_PASSENGERS_CAPACITY + '!');

	_passengers_Capacity = passengers_Capacity;
}

void Vehicle::setSpeedCapacity(int maximum_Speed_Capacity) {
	if (maximum_Speed_Capacity < GlobalConstants::MIN_SPEED_CAPACITY)
		throw std::invalid_argument("The min capacity of speed must be at least " + GlobalConstants::MIN_SPEED_CAPACITY + '!');

	_maximum_Speed_Capacity = maximum_Speed_Capacity;
}

void Vehicle::setBrand(const char* brand) {
	delete[] _brand;

	_brand = new (std::nothrow) char[strlen(brand) + 1];

	if (!_brand)
		throw std::bad_alloc();
}
