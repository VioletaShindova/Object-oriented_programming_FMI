#include "InfoCommand.h"

InfoCommand::InfoCommand(Library& lib, const std::string& isbnOrIssn) : Command(lib), isbnOrIssn(isbnOrIssn) 
{
	setMode(isbnOrIssn);
}

std::vector<Item*> InfoCommand::gatherRelevantItems() const
{
	std::vector<Item*> items;

	switch (mode)
	{
	case IsbnOrIssn::ISBN:
		items = lib.getOnlyOneTypeOfItem("Book");
		break;
	case IsbnOrIssn::ISSN:
		items = lib.getOnlyOneTypeOfItem("Periodical");
		break;
	}

	std::vector<Item*> series = lib.getOnlyOneTypeOfItem("Series");
	items.insert(items.end(), series.begin(), series.end());

	return items;
}

bool InfoCommand::printMatchFromItems(const std::vector<Item*>& items) const
{
	for (const Item* item : items)
	{
		if (!item) continue;

		const std::string& type = item->getType();

		switch (mode)
		{
		case IsbnOrIssn::ISBN:
			if (type == "Book") {
				const Book* book = dynamic_cast<const Book*>(item);
				if (book && isbnOrIssn == book->getISBN()) {
					std::cout << std::endl << book->getType() << ":\n";
					book->print();
					return true;
				}
			}
			else if (type == "Series") {
				const Series* series = dynamic_cast<const Series*>(item);
				if (series && isbnOrIssn == series->getISBN()) {
					std::cout << std::endl << series->getType() << ":\n";
					series->print();
					return true;
				}
			}
			break;

		case IsbnOrIssn::ISSN:
			if (type == "Periodical") {
				const Periodical* p = dynamic_cast<const Periodical*>(item);
				if (p && isbnOrIssn == p->getISSN()) {
					std::cout << std::endl << p->getType() << ":\n";
					p->print();
					return true;
				}
			}
			else if (type == "Series") {
				const Series* series = dynamic_cast<const Series*>(item);
				if (series && isbnOrIssn == series->getISSN()) {
					std::cout << std::endl << series->getType() << ":\n";
					series->print();
					return true;
				}
			}
			break;
		}
	}
	return false;
}

void InfoCommand::execute() const
{
	const std::vector<Item*> items = gatherRelevantItems();

	if (!printMatchFromItems(items)) {
		std::cout << "No item found with identifier: " << isbnOrIssn << "\n";
	}
}

bool InfoCommand::isExcutable() const
{
	return lib.isSomeoneLogged();
}

void InfoCommand::setMode(const std::string& isbnOrIssn)
{

	if (isbnOrIssn.size() >= 13 && isbnOrIssn.size() <= GlobalConstants::SIZE_ISBN &&
		isCorrectISBN(isbnOrIssn.c_str()))
	{
		mode = IsbnOrIssn::ISBN;
	}
	else if (isbnOrIssn.size() == GlobalConstants::SIZE_ISSN)
	{
		mode = IsbnOrIssn::ISSN;
	}
	else
	{
		throw std::invalid_argument("Invalid identifier format. Expected valid ISBN (13-20 chars) or ISSN (9 chars).");
	}
}
