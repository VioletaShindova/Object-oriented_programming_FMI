#pragma once
#include "Library.h"
#include "Command.h"

class AddNewsletterCommand : public Command
{
public:
	AddNewsletterCommand(Library& lib);

	void execute() const override;
	bool isExcutable() const override;
};

