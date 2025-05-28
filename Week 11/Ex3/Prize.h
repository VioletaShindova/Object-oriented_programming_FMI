#pragma once
#include <iostream>
#include <fstream>
class Prize
{
public:
	virtual ~Prize() noexcept {}

	virtual void visualize(std::ofstream& ofs) const = 0;

	inline unsigned getPrice() const noexcept { return price; }

	inline unsigned getPoints() const noexcept { return points; }

	void setPrice(int price);
	virtual void setPoints(int points);

protected:
	unsigned price = 0;
	unsigned points = 0;
private:
	
};

