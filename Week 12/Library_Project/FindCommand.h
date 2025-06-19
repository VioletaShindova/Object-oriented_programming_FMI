#pragma once
#include "Command.h"
#include "Library.h"

class FindCommand : public Command
{
public:
	FindCommand(Library& lib, const std::string& file,
		const std::string& option, const std::string& value,
		const std::string& sortKey, bool ascending, int top);

	void execute() const override;
	bool isExcutable() const override;

private:
	void sortItems(std::vector<Item*>& items) const;
	void filterItems(const std::vector<Item*>& all, std::vector<Item*>& result) const;
	bool shouldGoBefore(Item* a, Item* b) const;
	bool hasTag(const Book* b) const;
	bool hasTag(const Series* s) const;
	bool hasTag(const Periodical* p) const;

	std::string fileName;
	std::string option;
	std::string value;
	std::string sortKey;
	bool ascending;
	int top;
};

