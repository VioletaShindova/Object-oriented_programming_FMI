#pragma once
#include <iostream>
#pragma warning(disable : 4996)

namespace GlobalConstants {
	constexpr unsigned YEAR_OF_MANUFACTURE = 1885;
	constexpr unsigned MIN_PASSENGERS_CAPACITY = 1;
	constexpr unsigned MIN_SPEED_CAPACITY = 16;
	constexpr size_t MIN_DOORS_COUNT = 2;
	constexpr unsigned MIN_CAR_HORSEPOWER = 30;
	constexpr size_t MIN_SIZE_GEARS = 1;
}

class Vehicle
{
public:
	enum class Color {
		INVALID = -1,
		WHITE,
		YELLOW,
		ORANGE,
		RED,
		PURPLE,
		GREEN,
		BLUE,
		BLACK,
		COUNTER
	};

	Vehicle();

	Vehicle(Color color, const char* brand,
		int year_Of_Manufacture,
		int passengers_Capacity,
		int maximum_Speed_Capacity);

	Vehicle(const Vehicle& other);

	Vehicle& operator=(const Vehicle& other);

	virtual ~Vehicle() noexcept;

	inline Color getColor() const noexcept { return _color; }

	inline const char* getBrand() const noexcept { return _brand; }

	inline unsigned getYear_Of_Manufacture() const noexcept { return  _year_Of_Manufacture; }

	inline size_t getPassengers_Capacity() const { return _passengers_Capacity; }

	inline unsigned getMaximum_Speed_Capacity() const { return _maximum_Speed_Capacity; }

protected:
	Color _color;
	char* _brand;
	unsigned _year_Of_Manufacture;
	size_t _passengers_Capacity;
	unsigned _maximum_Speed_Capacity;

private:
	void setYearOfManufacture(int year_Of_Manufacture);

	void setCapacityOfPassengers(int passengers_Capacity);

	void setSpeedCapacity(int maximum_Speed_Capacity);

	void setBrand(const char* brand);

	void copyDynamic(const Vehicle& other);

	void freeDynamic() noexcept;
};

