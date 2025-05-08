#pragma once
#include "MyString.h"
#include <iostream>

class Ticket
{
public:
	Ticket();

	Ticket(const MyString& name, double price);

	void setPrice(double price);

	void print() const;

private:
	MyString name;
	double price;
};

