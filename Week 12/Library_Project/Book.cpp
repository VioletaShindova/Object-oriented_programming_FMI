#include "Book.h"
#pragma warning(disable : 4996)

Book::Book() : Book("unknown", {}, "xxx-x-xx-xxxxxx-x") {}

Book::Book(const std::string& author, const std::vector<std::string>& keyWords, const char* ISBN)
	: Item(), author("unknown"), keyWords({})
{
	setAuthor(author);
	setKeyWords(keyWords);
	setISBN(ISBN);
}

Book::Book(const std::string& title, const std::string& publisher, const std::string& genre, 
		   const std::string& description, int yearPublished, int rating, 
		   const std::string& author, std::vector<std::string> keyWords, const char* ISBN)
	: Item(title, publisher, genre, description, yearPublished, rating), author("unknown"), keyWords({}), ISBN("")
{
	setAuthor(author);
	setKeyWords(keyWords);
	setISBN(ISBN);
}

Book::Book(const Item& obj, const std::string& author, std::vector<std::string> keyWords, const char* ISBN)
	: Item(obj), author("unknown"), keyWords({}), ISBN("")
{
	setAuthor(author);
	setKeyWords(keyWords);
	setISBN(ISBN);
}

void Book::setAuthor(const std::string& author)
{
	if (author.empty())
		throw std::invalid_argument("There is no author\n");

	this->author = author;
}

void Book::setKeyWords(const std::vector<std::string>& keyWords)
{
	if (keyWords.empty())
		throw std::invalid_argument("There are no key words\n");

	this->keyWords = keyWords;
}

static bool isDigit(char symbol)
{
	return '0' <= symbol && symbol <= '9';
}

void Book::setISBN(const char* ISBN)
{
	if (!ISBN || strlen(ISBN) < 13 || strlen(ISBN) > GlobalConstants::SIZE_ISBN || !isCorrectISBN(ISBN)) //GlobalConstants::SIZE_ISBN=20
		throw std::invalid_argument("Invalid ISBN\n");

	strcpy(this->ISBN, ISBN);
}

const std::string& Book::getAuthor() const noexcept
{
	return author;
}

const std::vector<std::string>& Book::getKeyWords() const noexcept
{
	return keyWords;
}

const char* Book::getISBN() const noexcept
{
	return ISBN;
}

void Book::print() const
{
	std::cout << "Title: " << getTitle() << "\n";
	std::cout << "Author: " << getAuthor() << "\n";
	std::cout << "Publisher: " << getPublisher() << "\n";
	std::cout << "Genre: " << getGenre() << "\n";
	std::cout << "Description: " << getDescription() << "\n";
	std::cout << "Year: " << getYearPublished() << "\n";
	std::cout << "Rating: " << getRating() << "\n";
	std::cout << "ISBN: " << getISBN() << "\n";

	std::cout << "Keywords: ";
	for (const std::string& kw : keyWords) {
		std::cout << kw << " ";
	}

	std::cout << "\n";
}

void Book::saveToFile(const std::string& fileName) const
{
	//Item::saveToFile(fileName);

	if (fileName.empty())
		throw std::invalid_argument("Invalid file name\n");

	std::ofstream ofs(fileName, std::ios::app);

	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << getID() << "," << getTitle() << "," << getPublisher()<< "," << getGenre() << ","
		<< getDescription() << "," << getYearPublished() << "," << getRating();

	ofs << "," << author;

	// keyWords with ~ as separator
	ofs << ",";

	for (size_t i = 0; i < keyWords.size(); ++i) {
		ofs << keyWords[i];
		if (i != keyWords.size() - 1)
			ofs << "~";
	}

	ofs << "," << ISBN << std::endl;

	ofs.close();
}

void Book::saveAllToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open() || !ofs.good())
		throw std::runtime_error("Something wrong with stream - it is either bad or it can't be opened\n");

	ofs << getID() << "," << getTitle() << "," << getPublisher() << "," << getGenre() << ","
		<< getDescription() << "," << getYearPublished() << "," << getRating();

	ofs << "," << author;

	// keyWords with ~ as separator
	ofs << ",";

	for (size_t i = 0; i < keyWords.size(); ++i) {
		ofs << keyWords[i];
		if (i != keyWords.size() - 1)
			ofs << "~";
	}

	ofs << "," << ISBN << std::endl;
}

std::string Book::getType() const
{
	return "Book";
}

Book* Book::loadFromFile(const std::string& line)
{
	std::vector<std::string> tokens = split(line, ',');
	if (tokens.size() < 9) throw std::runtime_error("Invalid book format");

	unsigned id = parseToInt(tokens[0]);
	std::string title = tokens[1];
	std::string publisher = tokens[2];
	std::string genre = tokens[3];
	std::string description = tokens[4];
	int year = parseToInt(tokens[5]);
	int rating = parseToInt(tokens[6]);
	std::string author = tokens[7];
	std::vector<std::string> keywords = split(tokens[8], '~');
	std::string isbn = tokens[9];

	Book* b = new Book(title, publisher, genre, description, year, rating, author, keywords, isbn.c_str());

	return b;
}

Item* Book::clone() const
{
	return new Book(*this);
}