#pragma once
#include "Command.h"
#include "Library.h"

class LogoutCommand : public Command
{
public:
	LogoutCommand(Library& lib);

	void execute() const override;
	bool isExcutable() const override;
};

