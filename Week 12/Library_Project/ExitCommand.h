#pragma once
#include "Command.h"
#include "Library.h"

class ExitCommand : public Command
{
public: 
	ExitCommand(Library& lib);

	void execute() const override;
	bool isExcutable() const override;
};

