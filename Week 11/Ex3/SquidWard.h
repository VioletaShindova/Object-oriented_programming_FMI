#pragma once
#include "Prize.h"

class SquidWard : public Prize
{
public:
	SquidWard();

	SquidWard(int price, int points);

	void visualize(std::ofstream& ofs) const override;

	void setPoints(int points) override;
};

