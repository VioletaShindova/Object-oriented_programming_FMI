#pragma once
#include "Prize.h"

class Penguin: public Prize
{
public:
	Penguin();

	Penguin(int price, int points);

	void visualize(std::ofstream& ofs) const override;

	void setPoints(int points) override;
};

