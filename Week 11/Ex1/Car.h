#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
public:
	//enum class Model {
	//	INVALID = -1,
	//	SEDAN, 
	//	HATCHBACK, STATION_WAGON, 
	//	MINIVAN, 
	//	SMALL_SUV,
	//	CROSSOVER, 
	//	MIDSIZE_SUV, 
	//	FULL_SIZE_SUV, 
	//	PICKUP,
	//	COUNTER
	//};

	Car();

	Car(const std::string model, int count_Of_Doors, int engine_HorsePower);

	Car(Color color, const char* brand, int year_Of_Manufacture,
		int passengers_Capacity, int maximum_Speed_Capacity, 
		const std::string model, int count_Of_Doors, int engine_HorsePower);

	Car(const Vehicle& other, const std::string model, int count_Of_Doors, int engine_HorsePower);

	inline std::string getModel() const noexcept { return _model; }

	inline size_t getCount_Of_Doors() const noexcept { return _count_Of_Doors; }

	inline unsigned getEngine_HorsePower() const noexcept { return _engine_HorsePower; }

private:
	void setDoorsCount(int count_Of_Doors);

	void setEngineHorsePower(int engine_HorsePower);
	
	//Model _model;
	std::string _model;
	size_t _count_Of_Doors;
	unsigned _engine_HorsePower;
};

