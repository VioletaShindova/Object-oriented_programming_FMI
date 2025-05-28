#include "Penguin.h"

Penguin::Penguin() : Prize() {}

Penguin::Penguin(int price, int points) {
	setPrice(price);
	setPoints(points);
}

void Penguin::visualize(std::ofstream& ofs) const
{
	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << "Penguin - " << points << std::endl;
}

void Penguin::setPoints(int points) {
	if (points < 0 || points > 50)
		throw std::invalid_argument("Points must be above 0 and less than 50!");

	this->points = points;
}
