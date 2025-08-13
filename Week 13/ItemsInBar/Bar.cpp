#include "Bar.hpp"
#include "Drink.hpp"
#include "Alcoholic.hpp"
#include "NonAlcoholic.h"

unsigned Bar::countOfAllDrinks = 0;
unsigned Bar::drinksSold = 0;
unsigned Bar::mlSold = 0;

Bar::Bar() : Bar(1) {}

Bar::Bar(int capacity) 
	:capacity(0)
{
	setCapacity(capacity);
}

Bar::Bar(const Bar& other) : size(other.size), capacity(other.capacity)
{
	copyDynamic(other);
}

Bar& Bar::operator=(const Bar& other)
{
	if (this != &other)
	{
		size = other.size;
		capacity = other.capacity;

		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Bar::~Bar()
{
	freeDynamic();
}

void Bar::setCapacity(int capacity)
{
	if (capacity < 0)
		throw std::invalid_argument("Capcity must be a positve number\n");

	Drink** temp = new (std::nothrow) Drink * [capacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < this->size; i++)
	{
		Drink* tempDrink = drinks[i] ? drinks[i]->clone() : nullptr;

		temp[i] = tempDrink;
	}

	for (size_t i = 0; i < this->size; i++)
		delete drinks[i];	

	delete[] drinks;

	drinks = temp;
	this->capacity = capacity;
}

void Bar::addDrink(const Drink* drinkToAdd)
{
	if (!drinkToAdd || countOfAllDrinks + 1 > GlobalConstants::DRINKS_CAPACITY)
		throw std::invalid_argument("Invalid drink or out of space\n");

	for (size_t i = 0; i < size; i++)
	{
		if (*drinkToAdd == *drinks[i])
		{
			countOfAllDrinks++;
			drinks[i]->setCounOfEachDrink(1);
			return;
		}
	}

	if (size + 1 > capacity)
		resize();

	drinks[size] = drinkToAdd->clone();
	drinks[size++]->setCounOfEachDrink(1);
	countOfAllDrinks++;
}

void Bar::addDrink(const Drink* drinkToAdd, int count)
{
	if (!drinkToAdd || countOfAllDrinks + 1 > GlobalConstants::DRINKS_CAPACITY)
		throw std::invalid_argument("Invalid drink or out of space\n");

	for (size_t i = 0; i < size; i++)
	{
		if (*drinkToAdd == *drinks[i])
		{
			countOfAllDrinks += count;
			drinks[i]->setCounOfEachDrink(count);
			return;
		}
	}

	if (size + 1 >= capacity)
		resize();

	drinks[size] = drinkToAdd->clone();
	drinks[size++]->setCounOfEachDrink(count);
	countOfAllDrinks += count;
}

void Bar::getDrink()
{
	if (!size)
		throw std::logic_error("There are no drinks\n");

	bool res = false;
	size_t tempCount = 0;
	size_t tempInd = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (drinks[i] && dynamic_cast<const NonAlcoholic*>(drinks[i]))
		{
			if (drinks[i]->getCountOfEachDrink() > 0 && drinks[i]->getCountOfEachDrink() > tempCount)
			{
				tempInd = i;
				tempCount = drinks[i]->getCountOfEachDrink();
				res = true;
			}
		}
	}

	if (res)
	{
		increaseMLSold(drinks[tempInd]->getML());
		increaseDrinkSold();
		drinks[tempInd]->setCounOfEachDrink(-1);
	}
}

void Bar::getAlcoholDrink()
{
	if (!size)
		throw std::logic_error("There are no drinks\n");

	bool res = false;
	size_t tempCount = 0;
	size_t tempInd = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (drinks[i] && dynamic_cast<const Alcoholic*>(drinks[i]))
		{
			if (drinks[i]->getCountOfEachDrink() > 0 && drinks[i]->getCountOfEachDrink() > tempCount)
			{
				tempInd = i;
				tempCount = drinks[i]->getCountOfEachDrink();
				res = true;
			}
		}
	}

	if (res)
	{
		increaseMLSold(drinks[tempInd]->getML());
		increaseDrinkSold();
		drinks[tempInd]->setCounOfEachDrink(-1);
	}
}

void Bar::getDrink(const Drink* drinkToGet)
{
	if (!drinkToGet || !size)
		throw std::invalid_argument("Invalid drink or there are no drinks\n");

	bool res = false;

	for (size_t i = 0; i < size; i++)
	{
		if (*drinkToGet == *drinks[i])
		{
			if (drinks[i]->getCountOfEachDrink() >= 0)
			{
				drinks[i]->setCounOfEachDrink(-1);
				countOfAllDrinks--;
				increaseMLSold(drinkToGet->getML());
				increaseDrinkSold();
				return;
			}
			else
				throw std::logic_error("Can't remove a drink that is unavailable");
		}
	}

	if (!res)
		std::cout << "Not found\n";
}

unsigned Bar::getAlocholDrinksSold()
{
	return drinksSold;
}

unsigned Bar::getMLSold()
{
	return mlSold;
}

void Bar::increaseDrinkSold()
{
	drinksSold++;
}

void Bar::increaseMLSold(unsigned ml)
{
	mlSold += ml;
}

void Bar::freeDynamic()
{
	for (size_t i = 0; i < size; i++)
	{
		delete drinks[i];
	}
	delete[] drinks;

	drinks = nullptr;
}

void Bar::copyDynamic(const Bar& other)
{
	Drink** newDrinks = new (std::nothrow) Drink * [other.capacity];

	if (!newDrinks)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.size; i++)
	{
		try {
			newDrinks[i] = other.drinks[i] ? other.drinks[i]->clone() : nullptr;
		}
		catch (const std::bad_alloc& bad_alloc)
		{
			for (size_t j = 0; j < i; j++)
			{
				delete newDrinks[j];
			}
			delete[] newDrinks;
			throw bad_alloc;
		}
	}

	this->drinks = newDrinks;
}

void Bar::resize()
{
	Drink** temp = new (std::nothrow) Drink * [capacity * 2 + 1] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		try {
			temp[i] = drinks[i] ? drinks[i]->clone() : nullptr;
		}
		catch (const std::bad_alloc& bad_alloc)
		{
			for (size_t j = 0; j < i; j++)
			{
				delete temp[j];
			}
			delete[] temp;
			throw bad_alloc;
		}
	}

	for (size_t i = 0; i < size; i++)
		delete drinks[i];
	delete[] drinks;
	
	drinks = temp;
	((capacity *= 2) += 1);
}