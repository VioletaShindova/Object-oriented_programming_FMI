#pragma once
#include "Command.h"
#include "Library.h"
#include "HelperFunctions.h"
#include <string>

class InfoCommand : public Command
{
public:
	InfoCommand(Library& lib, const std::string& isbnOrIssn);
	void execute() const override;
	bool isExcutable() const override;

private:
	void setMode(const std::string& isbnOrIssn);
	std::vector<Item*> gatherRelevantItems() const;
	bool printMatchFromItems(const std::vector<Item*>& items) const;

	std::string isbnOrIssn;

	enum class IsbnOrIssn {ISBN, ISSN} mode;
};

