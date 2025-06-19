#include "InfoCommand.h"

InfoCommand::InfoCommand(Library& lib, const std::string& isbnOrIssn) : Command(lib), isbnOrIssn(isbnOrIssn) {}

void InfoCommand::execute() const
{
	Item* item;
	if (isbnOrIssn.size() == GlobalConstants::SIZE_ISBN) {
		if (item = lib.getInfoOfItem("books.txt", isbnOrIssn)) {
			item->print();
			return;
		}
		if (item = lib.getInfoOfItem("series.txt", isbnOrIssn)) {
			item->print();
			return;
		}
	}
	else if (isbnOrIssn.size() == GlobalConstants::SIZE_ISSN) {
		if (item = lib.getInfoOfItem("newsletters.txt", isbnOrIssn)) {
			item->print();
			return;
		}
		if (item = lib.getInfoOfItem("series.txt", isbnOrIssn)) {
			item->print();
			return;
		}
	}
	else {
		std::cout << "Invalid identifier format. Expected ISBN (17 chars) or ISSN (9 chars).\n";
		return;
	}

	if (!item) {
		std::cout << "No item found with ISBN/ISSN: " << isbnOrIssn << "\n";
	}
}

bool InfoCommand::isExcutable() const
{
	return lib.isSomeoneLogged();
}
