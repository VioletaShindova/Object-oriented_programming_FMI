#pragma once
#include "Command.h"
#include "Library.h"

class PrintCommand : public Command
{
public:
	PrintCommand(Library& lib, const std::string& fileName);

	void execute() const override;
	bool isExcutable() const override;

	void setFileName(const std::string& fileName);
private:
	std::string fileName;

};

