#include "Item.h"

unsigned Item::currentID = 1;

Item::Item():Item("unknown", "unknown", "unknown", "unknown", 0, 0) {}

Item::Item(const std::string& title, const std::string& publisher, const std::string& genre, const std::string& description, int yearPublished, int rating)
	: title("unknown"), publisher("unknown"), genre("unknown"), description("unknown"), yearPublished(0), rating(0)
{
	setTitle(title);
	setPublisher(publisher);
	setGenre(genre);
	setDescription(description);
	setYearPublished(yearPublished);
	setRating(rating);

	readIDFromTextFile("lastID.txt");
	id = currentID++;
	writeIDToTextFile("lastID.txt");
}

void Item::setTitle(const std::string& title)
{
	if (title.empty())
		throw std::invalid_argument("Title is empty\n");

	this->title = title;
}

void Item::setPublisher(const std::string& publisher)
{
	if (publisher.empty())
		throw std::invalid_argument("Published is empty\n");

	this->publisher = publisher;
}

void Item::setGenre(const std::string& genre)
{
	if (genre.empty())
		throw std::invalid_argument("Genre is empty\n");

	this->genre = genre;
}

void Item::setDescription(const std::string& description)
{
	if (description.empty())
		throw std::invalid_argument("Description is empty\n");

	this->description = description;
}

void Item::setYearPublished(int yearPublished)
{
	if (yearPublished < 0)
		throw std::invalid_argument("Invalid year\n");

	this->yearPublished = yearPublished;
}

void Item::setRating(int rating)
{
	if (rating < 0)
		throw std::invalid_argument("Invalid rating\n");

	this->rating = rating;
}

const std::string& Item::getTitle() const noexcept
{
	return title;
}

const std::string& Item::getPublisher() const noexcept
{
	return publisher;
}

const std::string& Item::getGenre() const noexcept
{
	return genre;
}

const std::string& Item::getDescription() const noexcept
{
	return description;
}

unsigned Item::getYearPublished() const noexcept
{
	return yearPublished;
}

unsigned Item::getRating() const noexcept
{
	return rating;
}

unsigned Item::getID() const noexcept
{
	return id;
}

void Item::writeIDToTextFile(const char* fileName)
{
	if (!fileName)
		throw std::invalid_argument("Invalid file name\n");

	std::ofstream ofs(fileName);

	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << currentID;

	ofs.close();
}

void Item::readIDFromTextFile(const char* fileName)
{
	if (!fileName)
		throw std::invalid_argument("Invalid file name\n");

	std::ifstream ifs(fileName);

	if (!ifs.is_open())
		throw std::runtime_error("Can't open file\n");

	ifs >> currentID;

	ifs.close();
}

//void Item::saveToFile(const std::string& fileName) const
//{
//	if (fileName.empty())
//		throw std::invalid_argument("Invalid file name\n");
//
//	std::ofstream ofs(fileName, std::ios::app);
//
//	if (!ofs.is_open())
//		throw std::runtime_error("Can't open file\n");
//
//	ofs << id << "," << title << "," << publisher << "," << genre << ","
//		<< description << "," << yearPublished << "," << rating;
//
//	ofs.close();
//}
