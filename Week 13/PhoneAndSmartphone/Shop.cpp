#include "Shop.hpp"
#include "Phone.hpp"
#include <iostream>

Shop::Shop() : Shop(0) {}

Shop::Shop(double budget) : budget(0), phones(nullptr), size(0), capacity(1)
{
	setBudget(budget);
}

Shop::Shop(const Shop& other) : currentPrice(other.currentPrice), budget(other.budget), size(other.size), capacity(other.capacity)
{
	copyDynamic(other);
}

Shop& Shop::operator=(const Shop& other)
{
	if (this != &other)
	{
		currentPrice = other.currentPrice;
		size = other.size;
		capacity = other.capacity;
		budget = other.budget;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Shop::~Shop() noexcept
{
	freeDynamic();
}

void Shop::setBudget(double budget)
{
	if (budget < 0)
		throw std::invalid_argument("Budget must be a positive number\n");

	this->budget = budget;
}

bool Shop::addPhone(const Phone* phone)
{
	if (!phone || phone->getPrice() + currentPrice > budget)
		throw std::logic_error("Can't add the phone\n");

	if (size + 1 >= capacity)
		resize();

	Phone* temp = new (std::nothrow) Phone(*phone); // deep copy!!!!

	if (!temp)
		throw std::bad_alloc();

	phones[size++] = temp;
	currentPrice += phone->getPrice();
	//phones[size++] = const_cast<Phone*>(phone); //shallow copy
	return true;
}

bool Shop::removePhone(const char* model, const char* brand)
{
	if (!model || !brand || !strlen(model) || !strlen(brand))
		throw std::logic_error("Can't remove phone");

	bool found = false;
	double price = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (areEqual(*phones[i], model, brand))
		{
			price = phones[i]->getPrice();
			std::swap(phones[i], phones[size - 1]);
			found = true;
			break;
		}
	}

	if (!found)
		return false;
	
	size_t tempSize = size - 1;
	Phone** temp = new (std::nothrow) Phone * [tempSize];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < tempSize; i++)
	{
		Phone* tempPhone = new (std::nothrow) Phone(*phones[i]);

		if (!tempPhone)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				delete temp[j];
			}
			delete[] temp;
			throw std::bad_alloc();
		}

		temp[i] = tempPhone;
	}

	for (size_t i = 0; i < size; i++)
	{
		delete phones[i];
	}

	delete[] phones;
	phones = temp;

	currentPrice -= price;
	budget += price;
	size--;

	return true;
}

void Shop::resize()
{
	Phone** temp = new (std::nothrow) Phone * [capacity * 2 + 1];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		Phone* tempPhone = new (std::nothrow) Phone(*phones[i]);

		if (!tempPhone)
		{
			for (int j = i - 1; j  >= 0; j--)
			{
				delete temp[j];
			}
			delete[] temp;
			throw std::bad_alloc();
		}

		temp[i] = tempPhone;
	}

	for (size_t i = 0; i < size; i++)
	{
		delete this->phones[i];
	}

	delete[] phones;
	phones = temp;

	((capacity *= 2) += 1);
}

void Shop::freeDynamic()
{
	for (size_t i = 0; i < size; i++)
	{
		delete phones[i];
	}
	delete[] phones;
	phones = nullptr;
}

void Shop::copyDynamic(const Shop& other)
{
	Phone** phones = new (std::nothrow) Phone * [other.capacity];

	if (!phones)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.size; i++)
	{
		Phone* temp = new (std::nothrow) Phone(*other.phones[i]);
		if (!temp)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				delete phones[j];
			}
			delete[] phones;
			throw std::bad_alloc();
		}

		phones[i] = temp;
	}

	for (size_t i = 0; i < size; i++)
	{
		delete this->phones[i];
	}
	delete[] this->phones;
	this->phones = phones;
}
