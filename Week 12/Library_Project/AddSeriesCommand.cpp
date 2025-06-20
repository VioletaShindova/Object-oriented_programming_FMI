#include "AddSeriesCommand.h"

AddSeriesCommand::AddSeriesCommand(Library& lib) : Command(lib) {}

void AddSeriesCommand::execute() const
{
	std::cout << "Author: ";
	std::string author = readLine(std::cin);
	if (author == "qw") 
		throw std::runtime_error("Declined adding new item\n");

	std::cout << "Title: ";
	std::string title = readLine(std::cin);
	if (title == "qw") 
		throw std::runtime_error("Declined adding new item\n");

	std::cout << "Publisher: ";
	std::string publisher = readLine(std::cin);
	if (publisher == "qw") 
		throw std::runtime_error("Declined adding new item\n");

	std::cout << "Genre: ";
	std::string genre = readLine(std::cin);
	if (genre == "qw") 
		throw std::runtime_error("Declined adding new item\n");

	std::cout << "Description: ";
	std::string description = readLine(std::cin);
	if (description == "qw") 
		throw std::runtime_error("Declined adding new item\n");

	std::cout << "Year published: ";
	std::string temp = readLine(std::cin);
	if (temp == "qw") 
		throw std::runtime_error("Declined adding new item\n");
	int yearPublished = parseToInt(temp);

	std::cout << "Month published (1-12): ";
	temp = readLine(std::cin);
	if (temp == "qw") 
		throw std::runtime_error("Declined adding new item\n");
	int monthPublished = parseToInt(temp);

	std::cout << "Count: ";
	temp = readLine(std::cin);
	if (temp == "qw") 
		throw std::runtime_error("Declined adding new item\n");
	int count = parseToInt(temp);

	std::cout << "Keywords (space-separated): ";
	const std::vector<std::string> keyWords = split(readLine(std::cin), ' ');
	for (const std::string& kw : keyWords) {
		if (kw == "qw")
			throw std::runtime_error("Declined adding new item\n");
	}

	std::cout << "Rating: ";
	temp = readLine(std::cin);
	if (temp == "qw") 
		throw std::runtime_error("Declined adding new item\n");
	int rating = parseToInt(temp);

	std::cout << "ISBN: ";
	std::string ISBN = readLine(std::cin);
	if (ISBN == "qw") 
		throw std::runtime_error("Declined adding new item\n");

	std::cout << "ISSN: ";
	std::string ISSN = readLine(std::cin);
	if (ISSN == "qw") 
		throw std::runtime_error("Declined adding new item\n");

	std::vector<Periodical::Contents> contents;

	while (true) {
		std::cout << "Add content block? (yes/qw): ";
		std::string response = readLine(std::cin);
		if (response == "qw" || response == "no") 
			break;

		std::cout << "  Content title: ";
		std::string currTitle = readLine(std::cin);
		if (currTitle == "qw")
			break;

		std::cout << "  Content author: ";
		std::string currAuthor = readLine(std::cin);
		if (currAuthor == "qw")
			break;

		std::cout << "  Content keywords (space-separated): ";
		std::vector<std::string> currKW = split(readLine(std::cin), ' ');
		for (const std::string& keyWord : currKW)
			if (keyWord == "qw")
				throw std::runtime_error("Declined adding new item\n");

		contents.emplace_back(currTitle, currAuthor, currKW);
	}

	Series* newSeries = new Series(author, title, publisher, genre, description,
								   yearPublished, monthPublished, count, keyWords,
								   static_cast<double>(rating),  
								   ISBN.c_str(), ISSN.c_str(), contents);

	lib.addItem(newSeries);

	std::cout << "Series successfully added!\n";
}

bool AddSeriesCommand::isExcutable() const
{
	return lib.isSomeoneLogged();
}
