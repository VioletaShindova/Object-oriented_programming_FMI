#include "Book.hpp"
#include "helpers.hpp"
#include "iohelpers.hpp"

#pragma warning(disable : 4996)

unsigned Book::lastID = 0;

Book::Book() : Book("unknown", "unknown", 0) {}

Book::Book(const char* name, const char* author, int pages)
	: name(nullptr), author(nullptr), pages(0), currID(incrementID())
{
	try {
		setPages(pages);
	}
	catch (std::invalid_argument& inv_arg) {
		std::cout << inv_arg.what();
		throw inv_arg;
	}

	formatID();
	setName(name);

	try {
		setAuthor(author);
	}
	catch (std::bad_alloc& bad_alloc) {
		delete[] name;
		std::cout << bad_alloc.what();
		throw bad_alloc;
	}
	catch (std::invalid_argument& inv_arg) {
		delete[] name;
		std::cout << inv_arg.what();
		throw inv_arg;
	}
}

Book::Book(const Book& other) : pages(other.pages), currID(other.currID)
{
	std::memcpy(id, other.id, GlobalConstants::ID_SIZE);
	id[GlobalConstants::ID_SIZE] = '\0'; 
	copyDynamic(other);
}

//Book& Book::operator=(const Book& other)
//{
//	if (this != &other) {
//		pages = other.pages;
//
//		freeDynamic();
//		copyDynamic(other);
//	}
//	return *this;
//}

Book::~Book() noexcept
{
	freeDynamic();
}

void Book::setName(const char* name)
{
	if (!name || strlen(name) == 0)
		throw std::invalid_argument("Invalid name\n");

	char* tempName = new (std::nothrow) char[strlen(name) + 1];

	if (!tempName)
		throw std::bad_alloc();

	strcpy(tempName, name);
	delete[] this->name;
	this->name = tempName;
}

void Book::setAuthor(const char* author)
{
	if (!author || strlen(author) == 0)
		throw std::invalid_argument("Invalid author\n");

	char* tempAuthor = new (std::nothrow) char[strlen(author) + 1];

	if (!tempAuthor)
		throw std::bad_alloc();

	strcpy(tempAuthor, author);
	delete[] this->author;
	this->author = tempAuthor;
}

bool Book::writeToStream(std::ostream& os) const
{
	if (!os.good())
		return false;

	os << name << ", " << author << ", " << pages << ", ";

	for (size_t i = 0; i < GlobalConstants::ID_SIZE; i++)
	{
		os << id[i];
	}

	os << '\n';

	return true;
}

bool Book::readFromStream(std::istream& is)
{
	if (!is.good())
		return false;

	char buffer[128];

	is.getline(buffer, 128, ',');
	skipSpaces(is, ' ');

	char* tempName = new (std::nothrow) char[strlen(buffer) + 1];
	if (!tempName)
		throw std::bad_alloc();
	strcpy(tempName, buffer);

	is.getline(buffer, 128, ',');
	skipSpaces(is, ' ');

	char* tempAuthor = new (std::nothrow) char[strlen(buffer) + 1];
	if (!tempAuthor) {
		delete[] tempName;
		throw std::bad_alloc();
	}
	strcpy(tempAuthor, buffer);

	int pages;
	is >> pages;

	if (!is) {
		is.clear();
		skipSpaces(is, ',');
	}
	skipSpaces(is, ' ');

	char tempID[GlobalConstants::ID_SIZE + 1];
	for (size_t i = 0; i < GlobalConstants::ID_SIZE; i++) {
		if (!is.get(tempID[i]))
			tempID[i] = '0';
	}
	tempID[GlobalConstants::ID_SIZE] = '\0';
	is.sync();

	// ако дотук всичко е ОК, присвояваме
	delete[] name;
	name = tempName;

	delete[] author;
	author = tempAuthor;

	this->pages = pages;
	memcpy(id, tempID, GlobalConstants::ID_SIZE);
	id[GlobalConstants::ID_SIZE] = '\0'; // предпазно

	return true;
}

void Book::setPages(int pages)
{
	if (pages < 0)
		throw std::invalid_argument("Pages must be a positive number\n");

	this->pages = pages;
}

void Book::formatID()
{
	if (currID > GlobalConstants::MAX_VALUE_BOOKS)
		throw std::range_error("You reached max capacity\n");

	unsigned ind = GlobalConstants::ID_SIZE - 1;
	unsigned tempID = currID;
	while (tempID / 10 != 0)
	{
		id[ind--] = ((tempID % 10) + '0');
		tempID /= 10;
	}
}

void Book::copyDynamic(const Book& other)
{
	char* tempName = new (std::nothrow) char[strlen(other.name) + 1];

	if (!tempName)
		throw std::bad_alloc();

	strcpy(tempName, other.name);
	
	char* tempAuthor = new (std::nothrow) char[strlen(other.author) + 1];

	if (!tempAuthor) {
		delete[] tempName;
		throw std::bad_alloc();
	}

	strcpy(tempAuthor, other.author);
	delete[] name;
	name = tempName;
	delete[] author;
	author = tempAuthor;
}

void Book::freeDynamic()
{
	delete[] name;
	delete[] author;

	name = nullptr;
	author = nullptr;
}

unsigned Book::incrementID()
{
	return ((lastID+1) > GlobalConstants::MAX_VALUE_BOOKS) ? throw std::range_error("You reached max capacity\n") : ++lastID;
}

bool areEqual(const Book* lhs, const Book* rhs)
{
	return strcmp(lhs->getID(), rhs->getID()) == 0 &&
		strcmp(lhs->getName(), rhs->getName()) == 0 &&
		strcmp(lhs->getAuthor(), rhs->getAuthor()) == 0 &&
		lhs->getPages() == rhs->getPages();
}
