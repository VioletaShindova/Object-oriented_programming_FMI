#include "Bar.hpp"
#include "Drink.hpp"

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

	Drink** temp = new (std::nothrow) Drink * [capacity * 2 + 1] {nullptr};

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
	this->capacity = capacity * 2 + 1;
}

void Bar::addDrink(const Drink* drinkToAdd)
{
	if (!drinkToAdd)
		throw std::invalid_argument("Invalid drink\n");

	for (size_t i = 0; i < size; i++)
	{
		if (drinkToAdd == drinks[i])
		{
			countOfEachDrink++;
			return;
		}
	}

	if (size + 1 >= capacity)
		resize();

	drinks[size++] = drinkToAdd->clone();
	countOfEachDrink++;
}

void Bar::addDrink(const Drink* drinkToAdd, int count)
{
	if (!drinkToAdd || count <= 0)
		throw std::invalid_argument("Invalid drink\n");

	for (size_t i = 0; i < size; i++)
	{
		if (*drinkToAdd == *drinks[i])
		{
			countOfEachDrink += count;
			return;
		}
	}

	if (size + 1 >= capacity)
		resize();

	drinks[size++] = drinkToAdd->clone();
	countOfEachDrink += count;
}

void Bar::getDrink(const Drink* drinkToGet)
{
	if (!drinkToGet)
		throw std::invalid_argument("Invalid drink\n");

	bool res = false;

	for (size_t i = 0; i < size; i++)
	{
		if (*drinkToGet == *drinks[i])
		{
			if (countOfEachDrink)
			{
				countOfEachDrink--;
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
	Drink** drinks = new (std::nothrow) Drink * [other.capacity];

	if (!drinks)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.size; i++)
	{
		try {
			drinks[i] = other.drinks[i] ? other.drinks[i]->clone() : nullptr;
		}
		catch (const std::bad_alloc& bad_alloc)
		{
			for (size_t j = 0; j < i; j++)
			{
				delete drinks[j];
			}
			delete[] drinks;
			throw bad_alloc;
		}
	}

	this->drinks = drinks;
}

void Bar::resize()
{
	Drink** temp = new (std::nothrow) Drink * [capacity * 2 + 1];

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