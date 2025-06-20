#include "AddNewsletterCommand.h"

AddNewsletterCommand::AddNewsletterCommand(Library& lib) : Command(lib) {}

void AddNewsletterCommand::execute() const
{
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

	std::string temp;

	std::cout << "Year published: ";
	temp = readLine(std::cin);
	if (temp == "qw") 
		throw std::runtime_error("Declined adding new item\n");
	int yearPublished = parseToInt(temp);

	std::cout << "Rating: ";
	temp = readLine(std::cin);
	if (temp == "qw") 
		throw std::runtime_error("Declined adding new item\n");
	int rating = parseToInt(temp);

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

	std::cout << "ISSN: ";
	std::string ISSN = readLine(std::cin);
	if (ISSN == "qw") 
		throw std::runtime_error("Declined adding new item\n");

	std::vector<Periodical::Contents> contentVec;
	std::cout << "Add contents (type 'stop' as title to end):\n";

	while (true)
	{
		std::cout << "Content Title: ";
		std::string contentTitle = readLine(std::cin);
		if (contentTitle == "qw") 
			throw std::runtime_error("Declined adding new item\n");
		if (contentTitle == "stop") 
			break;

		std::cout << "Content Author: ";
		std::string contentAuthor = readLine(std::cin);
		if (contentAuthor == "qw") 
			throw std::runtime_error("Declined adding new item\n");

		std::cout << "Content KeyWords (space-separated): ";
		std::vector<std::string> keyWords = split(readLine(std::cin), ' ');
		for (const std::string& word : keyWords)
			if (word == "qw") 
				throw std::runtime_error("Declined adding new item\n");

		contentVec.emplace_back(contentTitle, contentAuthor, keyWords);
	}

	Periodical* newsletter = new Periodical(title, publisher, genre, description, yearPublished, rating, monthPublished, count, ISSN.c_str(), contentVec);

	lib.addItem(newsletter);

	std::cout << "Newsletter successfully added!\n";
}

bool AddNewsletterCommand::isExcutable() const
{
    return lib.isSomeoneLogged();
}
