#pragma once

#ifndef __SHOP_HEADER_INCLUDED

#define __SHOP_HEADER_INCLUDED

class Phone;

class Shop
{
public:
	Shop();
	explicit Shop(double budget);
	Shop(const Shop& other);
	Shop& operator=(const Shop& other);
	~Shop() noexcept;

	void setBudget(double budget);

	bool addPhone(const Phone* phone);
	bool removePhone(const char* model, const char* brand);

private:
	void resize();

	void freeDynamic();
	void copyDynamic(const Shop& other);


	Phone** phones;
	size_t size;
	size_t capacity;

	double currentPrice = 0;

	double budget;
};

#endif