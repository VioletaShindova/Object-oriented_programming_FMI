#pragma once
#include "Library.h"
#include "Command.h"

class AddSeriesCommand : public Command
{
public:
	AddSeriesCommand(Library& lib);

	void execute() const override;
	bool isExcutable() const override;
};

