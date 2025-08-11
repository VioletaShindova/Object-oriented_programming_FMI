#pragma once
#include "Resident.h"
#include <vector>

namespace GlobalConstants {
	constexpr double RENT_FOR_CENTRAL = 2.5;
	constexpr double RENT_FOR_SUBURB = 20.0/100; //??????. ?????? ?? ?????? ?????? ?? ???????? ? 20%. 
	constexpr double RANGE_OF_CENTER = 8.0; //min(n,m)/8
	constexpr double RANGE_OF_SUBURB = 6.0; // 6*min(n,m)/8.
}

enum class Location {
	INVALID = -1,
	CENTRAL,
	SUBURB
};

class Building
{
public:
	virtual ~Building() noexcept = default;

	struct Location {
	public:
	private:
		double width;
		double length;
	};

	virtual Building* clone() const = 0;
private:
	unsigned rent;
	Location location;
	std::vector<Resident*> tenants;
	size_t countOfTenants;
	size_t capacityOfTenants;
};

