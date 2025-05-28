#include "Prize.h"

void Prize::setPrice(int price)
{
	if (price < 0)
		throw std::invalid_argument("Price must be above 0!");

	this->price = price;
}

void Prize::setPoints(int points)
{
	if (points < 0 || points > 1500)
		throw std::invalid_argument("Points must be above 0 and less than 1500!");

	this->points = points;
}
