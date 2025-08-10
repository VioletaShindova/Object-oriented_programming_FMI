#include "Phone.hpp"
#include <iostream>
#pragma warning(disable : 4996)

Phone::Phone() : Phone("unknown", "unknown", 0) {}

Phone::Phone(const char* model, const char* brand, double price) : model(nullptr), brand(nullptr), price(0)
{
	setPrice(price);
	setModel(model);

	try {
		setBrand(brand);
	}
	catch (std::bad_alloc& bad_alloc)
	{
		delete[] model;
		std::cout << "Bad allocation\n";
		throw bad_alloc;
	}
	catch (std::invalid_argument& inv_arg)
	{
		delete[] model;
		std::cout << inv_arg.what();
		throw inv_arg;
	}
}

Phone::Phone(const Phone& other) :  price(other.price)
{
	copyDynamic(other);
}

Phone& Phone::operator=(const Phone& other)
{
	if (this != &other)
	{
		price = other.price;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Phone::~Phone() noexcept
{
	freeDynamic();
}

void Phone::setModel(const char* model)
{
	if (!model || strlen(model) == 0)
		throw std::invalid_argument("Invlaid model\n");

	char* temp = new (std::nothrow) char[strlen(model) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, model);
	delete[] this->model;
	this->model = temp;
}

void Phone::setBrand(const char* brand)
{
	if (!brand || strlen(brand) == 0)
		throw std::invalid_argument("Invlaid brand\n");

	char* temp = new (std::nothrow) char[strlen(brand) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, brand);
	delete[] this->brand;
	this->brand = temp;
}

void Phone::setPrice(double price)
{
	if (price < 0)
		throw std::invalid_argument("Invalid price\n");

	this->price = price;
}

void Phone::copyDynamic(const Phone& other)
{
	char* tempModel = new (std::nothrow) char[strlen(other.model) + 1];

	if (!tempModel)
		throw std::bad_alloc();
	
	strcpy(tempModel, other.model);

	char* tempBrand = new (std::nothrow) char[strlen(other.brand) + 1];

	if (!tempBrand)
	{
		delete[] tempModel;
		throw std::bad_alloc();
	}

	strcpy(tempBrand, other.brand);

	model = tempModel;
	brand = tempBrand;
}

void Phone::freeDynamic()
{
	delete[] model;
	delete[] brand;

	model = nullptr;
	brand = nullptr;
}

bool areEqual(const Phone& lhs, const char* model, const char* brand)
{
	return strcmp(lhs.getBrand(), brand) == 0 &&
		strcmp(lhs.getModel(), model) == 0;
}
