#pragma once
#include "Library.h"
#include "Command.h"

class AddBookCommand : public Command
{
public:
	AddBookCommand(Library& lib);

	void execute() const override;
	bool isExcutable() const override;
};

