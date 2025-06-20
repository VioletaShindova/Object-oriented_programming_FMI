#include "AddBookCommand.h"

AddBookCommand::AddBookCommand(Library& lib) : Command(lib) {}

void AddBookCommand::execute() const
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

	if (title == "qw")
		throw std::runtime_error("Declined adding new item\n");

	std::cout << "Genre: ";
	std::string genre = readLine(std::cin);

	if (title == "qw")
		throw std::runtime_error("Declined adding new item\n");

	std::cout << "Description: ";
	std::string description = readLine(std::cin);

	if (title == "qw")
		throw std::runtime_error("Declined adding new item\n");

	std::string temp;

	std::cout << "Year published: ";
	temp = readLine(std::cin);

	if (temp == "qw")
		throw std::runtime_error("Declined adding new item\n");

	int yearPublished = parseToInt(temp);

	std::cout << "Key words: ";
	const std::vector<std::string> keyWords = split(readLine(std::cin), ' ');

	for (const std::string& keyWord : keyWords) {
		if (keyWord == "qw")
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

	//const std::string& title, const std::string& publisher,
	/*const std::string& genre, const std::string& description,
	//int yearPublished, int rating, const std::string& author,
	//std::vector<std::string> keyWords, const char* ISBN*/
	Book* newBook = new Book(title, publisher, genre, description, yearPublished, rating, author, keyWords, ISBN.c_str());

	lib.addItem(newBook);

	std::cout << "Book successfully added!\n";
}

bool AddBookCommand::isExcutable() const
{
	return lib.isSomeoneLogged();
}
