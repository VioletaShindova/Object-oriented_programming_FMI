#include "Periodical.h"

Periodical::Contents::Contents(const std::string& contentTitle, const std::string& contentAuthor, const std::vector<std::string>& contentKeyWords)
	: contentTitle("unknown title content"), contentAuthor("unknown author of content"), contentKeyWords({})
{
	setContentTitle(contentTitle);
	setContentAuthor(contentAuthor);
	setContentKeyWords(contentKeyWords);
}

void Periodical::Contents::setContentTitle(const std::string& contentTitle)
{
	if (contentTitle.empty())
		throw std::invalid_argument("Title is empty\n");

	this->contentTitle = contentTitle;
}

void Periodical::Contents::setContentAuthor(const std::string& contentAuthor)
{
	if (contentAuthor.empty())
		throw std::invalid_argument("Author name is empty\n");

	this->contentAuthor = contentAuthor;
}

void Periodical::Contents::setContentKeyWords(const std::vector<std::string>& contentKeyWords)
{
	if (contentKeyWords.empty())
		throw std::invalid_argument("There are no content key words\n");

	this->contentKeyWords = contentKeyWords;
}

const std::string& Periodical::Contents::getContentTitle() const noexcept
{
	return contentTitle;
}

const std::string& Periodical::Contents::getContentAuthor() const noexcept
{
	return contentAuthor;
}

const std::vector<std::string>& Periodical::Contents::getContentKeyWords() const noexcept
{
	return contentKeyWords;
}

void Periodical::Contents::print() const
{
	std::cout << "  - Title: " << contentTitle << "\n";
	std::cout << "    Author: " << contentAuthor << "\n";
	std::cout << "    Keywords: ";
	for (const std::string& kw : contentKeyWords) {
		std::cout << kw << " ";
	}
	std::cout << "\n";
}

Periodical::Periodical() : Periodical((int)Month::INVALID, 0, nullptr, {}) {}

Periodical::Periodical(int monthPublished, int count, const char* ISSN, const std::vector<Contents>& content)
	: Item(), monthPublished(Month::INVALID), count(0), ISSN(""), content({})
{
	setMonthPublished(monthPublished);
	setCount(count);
	setISSN(ISSN);
	setContent(content);
}

Periodical::Periodical(const std::string& title, const std::string& publisher, 
					   const std::string& genre, const std::string& description, 
					   int yearPublished, int rating, 
					   int monthPublished, int count, const char* ISSN, const std::vector<Contents>& content)
	: Item(title, publisher, genre, description, yearPublished, rating), 
	monthPublished(Month::INVALID), count(0), ISSN(""), content({})
{
	setMonthPublished(monthPublished);
	setCount(count);
	setISSN(ISSN);
	setContent(content);
}

Periodical::Periodical(const Item& obj, int monthPublished, int count, const char* ISSN, const std::vector<Contents>& content)
	: Item(obj), monthPublished(Month::INVALID), count(0), ISSN(""), content({})
{
	setMonthPublished(monthPublished);
	setCount(count);
	setISSN(ISSN);
	setContent(content);
}

bool Periodical::isValidMonth(int monthPublished) const
{
	return ((int)Month::JANUARY <= monthPublished) && (monthPublished <= (int)Month::DECEMBER);
}

void Periodical::setMonthPublished(int monthPublished)
{
	if (!isValidMonth(monthPublished))
		throw std::invalid_argument("Month must be a number between 1 and 12\n");

	this->monthPublished = (Month)monthPublished;
}

void Periodical::setCount(int count)
{
	if (count < 0)
		throw std::invalid_argument("Count must be at least 0\n");

	this->count = count;
}

static bool isDigit(char symbol) {
	return '0' <= symbol && symbol <= '9';
}

bool Periodical::isValidISSN(const char* ISSN) const
{
	return (ISSN && strlen(ISSN) == GlobalConstants::SIZE_ISSN && isCorrectISSN(ISSN));
}

void Periodical::setISSN(const char* ISSN)
{
	if (!ISSN || strlen(ISSN) != GlobalConstants::SIZE_ISSN || !isValidISSN(ISSN))
		throw std::invalid_argument("ISSN must have exacty 9 symbols, 8 of which are numbers. Example: 1314-1237\n");

	strcpy(this->ISSN, ISSN);
}

void Periodical::setContent(const std::vector<Contents>& content)
{
	if (content.empty())
		throw std::invalid_argument("Invalid content\n");

	this->content = content;
}

Month Periodical::getMonthPublished() const noexcept
{
	return monthPublished;
}

size_t Periodical::getCount() const noexcept
{
	return count;
}

const char* Periodical::getISSN() const noexcept
{
	return ISSN;
}

const std::vector<Periodical::Contents>& Periodical::getContent() const noexcept
{
	return content;
}

void Periodical::print() const
{
	std::cout << "Title: " << getTitle() << "\n";
	std::cout << "Publisher: " << getPublisher() << "\n";
	std::cout << "Genre: " << getGenre() << "\n";
	std::cout << "Description: " << getDescription() << "\n";
	std::cout << "Year: " << getYearPublished() << "\n";
	std::cout << "Rating: " << getRating() << "\n";

	std::cout << "Month Published: ";
	if (monthPublished != Month::INVALID) {
		std::cout << (int)(monthPublished) << "\n";
	}
	else {
		std::cout << "Invalid\n";
	}

	std::cout << "Count: " << count << "\n";
	std::cout << "ISSN: " << ISSN << "\n";

	std::cout << "Contents:\n";
	for(const Periodical::Contents& eachContent : content)
	{
		eachContent.print();
	}
}

Item* Periodical::clone() const
{
	return new Periodical(*this);
}

void Periodical::saveToFile(const std::string& fileName) const
{
	//Item::saveToFile(fileName);
	
	if (fileName.empty())
		throw std::invalid_argument("Invalid file name\n");

	std::ofstream ofs(fileName, std::ios::app);
	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << getID() << "," << getTitle() << "," << getPublisher() << "," << getGenre() << ","
		<< getDescription() << "," << getYearPublished() << "," << getRating() << ","  // << FIXED HERE
		<< static_cast<int>(monthPublished) << "," << count << "," << ISSN;

	const std::vector<Contents>& allContents = getContent();
	if (!allContents.empty()) {
		ofs << "|";
		for (size_t i = 0; i < allContents.size(); ++i) {
			const Contents& content = allContents[i];
			ofs << content.getContentTitle() << "`" << content.getContentAuthor() << "`";
			const std::vector<std::string>& kws = content.getContentKeyWords();
			for (size_t j = 0; j < kws.size(); ++j) {
				ofs << kws[j];
				if (j != kws.size() - 1)
					ofs << "^";
			}
			if (i != allContents.size() - 1)
				ofs << "|";
		}
	}

	ofs << std::endl;
	ofs.close();
}

void Periodical::saveAllToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open() || !ofs.good())
		throw std::runtime_error("Invalid stream\n");

	ofs << getID() << "," << getTitle() << "," << getPublisher() << "," << getGenre() << ","
		<< getDescription() << "," << getYearPublished() << "," << getRating() << ","  // << FIXED HERE
		<< static_cast<int>(monthPublished) << "," << count << "," << ISSN;

	const std::vector<Contents>& allContents = getContent();
	if (!allContents.empty()) {
		ofs << "|";
		for (size_t i = 0; i < allContents.size(); ++i) {
			const Contents& content = allContents[i];
			ofs << content.getContentTitle() << "`" << content.getContentAuthor() << "`";
			const std::vector<std::string>& kws = content.getContentKeyWords();
			for (size_t j = 0; j < kws.size(); ++j) {
				ofs << kws[j];
				if (j != kws.size() - 1)
					ofs << "^";
			}
			if (i != allContents.size() - 1)
				ofs << "|";
		}
	}

	ofs << std::endl;
}

std::string Periodical::getType() const
{
	return "Periodical";
}

Periodical* Periodical::loadFromFile(const std::string& line)
{
	size_t sep = line.find('|');
	if (sep == std::string::npos)
		throw std::runtime_error("Invalid periodical format: missing content separator");

	std::vector<std::string> meta = split(line.substr(0, sep), ',');
	if (meta.size() < 10)
		throw std::runtime_error("Invalid periodical metadata format");

	std::vector<std::string> rawContents = split(line.substr(sep + 1), '|');

	unsigned id = parseToInt(meta[0]);
	std::string title = meta[1];
	std::string publisher = meta[2];
	std::string genre = meta[3];
	std::string description = meta[4];
	int yearPublished = parseToInt(meta[5]);
	int rating = parseToInt(meta[6]);
	int monthPublished = parseToInt(meta[7]);
	int count = parseToInt(meta[8]);
	std::string ISSN = meta[9];

	std::vector<Contents> parsedContents;
	for (const std::string& content : rawContents) {
		std::vector<std::string> parts = split(content, '`');
		if (parts.size() != 3)
			throw std::runtime_error("Invalid content format in periodical");

		std::string cTitle = parts[0];
		std::string cAuthor = parts[1];
		std::vector<std::string> cKeywords = split(parts[2], '^');

		parsedContents.emplace_back(cTitle, cAuthor, cKeywords);
	}

	Periodical* p = new Periodical(title, publisher, genre, description,
		yearPublished, rating, monthPublished, count, ISSN.c_str(), parsedContents);

	return p;
}