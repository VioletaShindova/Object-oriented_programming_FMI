#include "Pacman.h"

Pacman::Pacman() : Prize() {}

Pacman::Pacman(int price, int points) {
	setPrice(price);
	setPoints(points);
}

void Pacman::visualize(std::ofstream& ofs) const{
	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << "Pacman - " << points << std::endl;
}

void Pacman::setPoints(int points) {
	if (points < 0 || points > 150)
		throw std::invalid_argument("Points must be above 0 and less than 150!");

	this->points = points;
}
