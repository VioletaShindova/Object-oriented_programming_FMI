#pragma once
#include "Command.h"
#include "Library.h"

class PrintCommand : public Command
{
public:
	PrintCommand(Library& lib, const std::string& fileName);
	PrintCommand(Library& lib, const std::vector<Item*>& items);
	PrintCommand(Library& lib, const std::vector<User*>& users);

	void execute() const override;
	bool isExcutable() const override;

	void setFileName(const std::string& fileName);
private:
	std::string fileName;
	std::vector<Item*> itemsToPrint;
	std::vector<User*> usersToPrint;

	enum class Mode { FromFile, FromItems, FromUsers } mode;
};

