#pragma once
#include "Prize.h"

class Pacman : public Prize
{
public:
	Pacman();
	Pacman(int price, int points);

	void visualize(std::ofstream& ofs) const override;

	void setPoints(int points) override;
};

