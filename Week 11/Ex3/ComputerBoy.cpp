#include "ComputerBoy.h"

ComputerBoy::ComputerBoy() : Prize() {}

ComputerBoy::ComputerBoy(int price, int points) {
	setPrice(price);
	setPoints(points);
}

void ComputerBoy::visualize(std::ofstream& ofs) const {
	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << "computerBoy - " << points << std::endl;
}

void ComputerBoy::setPoints(int points) {
	if (points < 0 || points > 500)
		throw std::invalid_argument("Points must be above 0 and less than 500!");

	this->points = points;
}
