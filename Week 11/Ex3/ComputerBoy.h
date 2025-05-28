#pragma once
#include "Prize.h"

class ComputerBoy : public Prize
{
public:
	ComputerBoy();

	ComputerBoy(int price, int points);

	void visualize(std::ofstream& ofs) const override;

	void setPoints(int points) override;
};

