#pragma once

#ifndef __SMARTPHONE_HEADER_INCLUDED

#define __SMARTPHONE_HEADER_INCLUDED

#include "Phone.hpp"

class Smartphone : public Phone
{
public:
	Smartphone();
	Smartphone(const char* model, const char* brand, double price, const char* operatingSystem, int ram);
	Smartphone(const Phone& other, const char* operatingSystem, int ram);
	Smartphone(const Smartphone& other);
	Smartphone& operator=(const Smartphone& other);
	~Smartphone() noexcept;

	inline const char* getOperatingSystem() const noexcept { return operatingSystem; }
	inline unsigned getRAM() const noexcept { return ram; }

	void setOperatingSystem(const char* operatingSystem);
	void setRAM(int ram);

	void calculatePrice() const;//цената им се определя като към основната цена се добави лев за всеки GB от паметта.
private:
	void freeDynamic();
	void copyDynamic(const Smartphone& other);

	char* operatingSystem;
	unsigned ram;
};

#endif