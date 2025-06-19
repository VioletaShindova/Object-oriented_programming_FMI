#pragma once
#include "Command.h"
#include "Library.h"
#include <string>

class InfoCommand : public Command
{
public:
	InfoCommand(Library& lib, const std::string& isbnOrIssn);
	void execute() const override;
	bool isExcutable() const override;

private:
	std::string isbnOrIssn;
};

