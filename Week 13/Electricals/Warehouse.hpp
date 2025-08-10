#pragma once
#ifndef __WAREHOUSE_HEADER_INCLUDED_

#define __WAREHOUSE_HEADER_INCLUDED_

class Device;

class Warehouse
{
public:
	Warehouse();
	explicit Warehouse(int capacity);
	Warehouse(const Warehouse& other);
	Warehouse& operator=(const Warehouse& other);
	~Warehouse() noexcept;

	inline Device** getDevices() noexcept { return devices; }
	inline size_t getSize() const noexcept { return size; }
	inline double getCurrPower() const noexcept { return currPower; }

	void setCapacity(int capacity);

	bool addDevice(const Device* device);
	bool addDevice(const char* name, const char* producer);

	bool turnOn(const char* name);

	double getTotalPrice() const;
	void printAll() const;
private:
	void copyDynamic(const Warehouse& other);
	void freeDynamic();
	void resize();

	Device** devices;
	size_t size;
	size_t capacity;

	double currPower;
};

#endif