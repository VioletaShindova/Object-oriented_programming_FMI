#pragma once

#ifndef __BAR_HEADER_INCLUDED

#define __BAR_HEADER_INCLUDED
#include <iostream>

namespace GlobalConstants {
	constexpr size_t DRINKS_CAPACITY = 100;
}

class Drink;

class Bar
{
public:
	Bar();
	explicit Bar(int capacity);
	Bar(const Bar& other);
	Bar& operator=(const Bar& other);
	~Bar() noexcept;

	inline Drink** getDrinks() noexcept { return drinks; }
	inline size_t getSize() const noexcept { return size; }
	inline size_t getCapacity() const noexcept { return capacity; }

	void setCapacity(int capacity);

	void addDrink(const Drink* drinkToAdd);
	void addDrink(const Drink* drinkToAdd, int count);

	void getDrink();		
	void getAlcoholDrink();		
	void getDrink(const Drink* drinkToGet);		

	static unsigned getAlocholDrinksSold();
	static unsigned getMLSold();
private:
	static void increaseDrinkSold();
	static void increaseMLSold(unsigned ml);

	void freeDynamic();
	void copyDynamic(const Bar& other);

	void resize();

	Drink** drinks;
	size_t size;
	size_t capacity;
	static unsigned countOfAllDrinks;
	static unsigned drinksSold;
	static unsigned mlSold;
};

#endif