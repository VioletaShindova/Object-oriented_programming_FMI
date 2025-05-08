#include "Relation.h"
#include <iostream>
#include <fstream>

unsigned castCharSymbolToUInt(const char symbol)
{
	return symbol - '0';
}

bool isDigit(const char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

Relation::Relation(size_t size)
{
	if (!setSize(size))
	{
		throw std::exception("Invalid size!");
	}

	this->pair = new Pair[capacity];

	for (size_t i = 0; i < size; i++)
	{
		this->pair[i] = { 0,0 };
	}

	this->capacity -= size;
}

Relation::Relation(Pair* pair, size_t size)
{
	if (!setSize(size))
	{
		throw std::exception("Invalid size!");
	}

	if (!setPair(pair, size))
	{
		throw std::exception("Invalid pair!");
	}

	this->capacity -= size;
}

Relation::~Relation()
{
	delete[] this->pair;
}

bool Relation::setSize(size_t size)
{
	if (!isValidSize(size))
	{
		return false;
	}

	this->size = size;
	return true;
}

bool Relation::setPair(Pair* pair, size_t size)
{
	if (!pair)
	{
		return false;
	}

	this->pair = new Pair[this->capacity];

	for (size_t i = 0; i < size; i++)
	{
		this->pair[i] = pair[i];
	}

	return true;
}

size_t Relation::getSize() const
{
	return size;
}

const size_t Relation::getConstSize() const
{
	return size;
}

Pair* Relation::getPair() const
{
	return this->pair;
}

const Pair* Relation::getConstPair() const
{
	return this->pair;
}

bool Relation::readRelationFromFile(const char* fileName)
{
	if (!fileName)
		return false;
	std::ifstream ifs(fileName);

	if (!ifs.is_open())
		return false;

	unsigned tempIndex = 0;
	unsigned number = 0;
	unsigned secondNumber = 0;
	char ch;
	while (ifs.get(ch)) {

		if (isDigit(ch))
			((secondNumber *= 10) += castCharSymbolToUInt(ch));
		
		else if (ch == ',') {
			number = secondNumber;
			secondNumber = 0;
		}
		else if (ch == '}') {
			if (!hasCapacity() || tempIndex >= this->size)
			{
				std::cerr << "No capacity";
				return false;
			}

			Pair obj(number, secondNumber);
			this->pair[tempIndex++] = obj;

			number = 0; 
			secondNumber = 0;
		}
	}

	ifs.close();
	return true;
}

bool Relation::addPairToRelation(const Pair& pair)
{
	if (!hasCapacity())
		return false;

	this->pair[size++] = pair;
	--(this->capacity);
	return true;
}

bool Relation::writeRelationToFile(const char* fileName) const
{
	if (!fileName)
		return false;
	std::ofstream ofs(fileName);

	if (!ofs.is_open())
		return false;

	for (size_t i = 0; i < this->size; ++i)
	{
		ofs << '{' << this->pair[i].getFirstNumber()
			<< ',' << this->pair[i].getSecondNumber() << "} ";
	}

	ofs.close();
	return true;
}

void Relation::printRelations() const
{
	if (!pair)
	{
		std::cout << "Empty relations!";
		return;
	}

	unsigned index = 0;
	while (index < size)
	{
		std::cout << '{' << this->pair[index].getFirstNumber() << ',' << this->pair[index].getSecondNumber() << '}';
		index++;
	}
}

bool Relation::isValidSize(size_t size) const
{
	return 0 <= size;
}

bool Relation::hasCapacity() const
{
	return 0 < this->capacity;
}
