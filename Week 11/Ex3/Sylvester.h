#pragma once
#include "Prize.h"

class Sylvester : public Prize
{
public:
	Sylvester();

	Sylvester(int price, int points);

	void visualize(std::ofstream& ofs) const override;

	void setPoints(int points) override;
};

