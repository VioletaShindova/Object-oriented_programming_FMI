#pragma once
#include "Building.h"

class ModernBuilding : public Building
{
public:
	ModernBuilding();

	Building* clone() const override;

private:
};

