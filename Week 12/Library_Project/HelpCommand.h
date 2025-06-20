#pragma once
#include "Library.h"
#include "Command.h"

class HelpCommand : public Command
{
public:
	HelpCommand(Library& lib);

	void execute() const override;
	virtual bool isExcutable() const override;
};

