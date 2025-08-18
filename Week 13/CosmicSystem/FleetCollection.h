#pragma once

#ifndef __FLEET_COLLECTION_HEADER_INCLUDED_

#define __FLEET_COLLECTION_HEADER_INCLUDED_

class Ship;

class FleetCollection
{
public:
	FleetCollection();
	explicit FleetCollection(int capacity);
	FleetCollection(const FleetCollection& other);
	FleetCollection& operator=(const FleetCollection& other);
	~FleetCollection() noexcept;

	inline Ship** getShips() const noexcept { return ships; }
	inline size_t getSize() const noexcept { return size; }

	bool addShip(const Ship* toAddShip);
	bool removeShip(const Ship* toRemoveShip);

	const Ship* operator[](int index) const;

private:
	bool isFound(const Ship* toFind) const;
	void setCapacity(int capacity);
	void freeDynamic();
	void copyDynamic(const FleetCollection& other);
	void resize();

	Ship** ships;
	size_t size;
	size_t capacity;
};

#endif