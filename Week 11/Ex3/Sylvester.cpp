#include "Sylvester.h"

Sylvester::Sylvester() : Prize() {}

Sylvester::Sylvester(int price, int points) {
	setPrice(price);
	setPoints(points);
}

void Sylvester::visualize(std::ofstream& ofs) const{
	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << "sylvester - " << points << std::endl;
}

void Sylvester::setPoints(int points) {
	if (points < 0 || points > 1500)
		throw std::invalid_argument("Points must be above 0 and less than 1500!");

	this->points = points;
}
