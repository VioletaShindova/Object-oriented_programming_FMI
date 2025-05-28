#include "SquidWard.h"

SquidWard::SquidWard() : Prize() {}

SquidWard::SquidWard(int price, int points) {
	setPrice(price);
	setPoints(points);
}

void SquidWard::visualize(std::ofstream& ofs) const {
	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << "squidward  - " << points << std::endl;
}

void SquidWard::setPoints(int points) {
	if (points < 0 || points > 1000)
		throw std::invalid_argument("Points must be above 0 and less than 1000!");

	this->points = points;
}
