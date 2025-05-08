#include "Ticket.h"

Ticket::Ticket() : Ticket("", 0) {}

Ticket::Ticket(const MyString& name, double price) : name(name) {
	setPrice(price);
}

void Ticket::setPrice(double price) {
	if (price < 0) {
		throw std::invalid_argument("Price is negative number");
	}

	this->price = price;
}

void Ticket::print() const {
	std::cout << "Name: ";
	name.print();
	std::cout << "Price: " << price << std::endl;
}