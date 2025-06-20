#include "Series.h"

Series::Series() : Book(), Periodical(), Item() {}

Series::Series(const std::string& author, const std::string& title, 
	const std::string& publisher, const std::string& genre, 
	const std::string& description, int yearPublished, 
	int monthPublished, int count, const std::vector<std::string>& keyWords,
	double rating, const char* ISBN, const char* ISSN, const std::vector<Periodical::Contents>& content)
	: Book(author, keyWords, ISBN), 
	  Periodical(monthPublished, count, ISSN, content), 
	  Item(title, publisher, genre, description, yearPublished, rating)
{}

void Series::print() const
{
	Book::print();        // Title, Author, Publisher, Genre, Description, Year, Rating, ISBN, Keywords
	std::cout << "ISSN: " << getISSN() << "\n";

	std::cout << "Month Published: ";
	if (getMonthPublished() != Month::INVALID) {
		std::cout << (int)getMonthPublished() << "\n";
	}
	else {
		std::cout << "Invalid\n";
	}

	std::cout << "Count: " << getCount() << "\n";

	std::cout << "Contents:\n";
	for (const Periodical::Contents& eachContents : getContent()) {
		eachContents.print();
	}
}

Item* Series::clone() const
{
	return new Series(*this);
}

void Series::saveToFile(const std::string& fileName) const
{
	if (fileName.empty())
		throw std::invalid_argument("Invalid file name\n");

	std::ofstream ofs(fileName, std::ios::app);

	if (!ofs.is_open())
		throw std::runtime_error("Can't open file\n");

	ofs << getID() << "," << getTitle() << "," << getPublisher() << "," << getGenre() << ","
		<< getDescription() << "," << getYearPublished() << "," << getRating();

	ofs << "," << static_cast<int>(getMonthPublished()) << ","
		<< getCount() << ","
		<< getISSN() << ",";

	ofs << getAuthor() << ",";

	const std::vector<std::string>& kws = getKeyWords();
	for (size_t i = 0; i < kws.size(); ++i) {
		ofs << kws[i];
		if (i != kws.size() - 1)
			ofs << "~";
	}
	ofs << ",";

	ofs << getISBN();

	const std::vector<Contents>& contents = getContent();
	if (!contents.empty()) {
		ofs << "|";
		for (size_t i = 0; i < contents.size(); ++i) {
			const Contents& singleContent = contents[i];
			ofs << singleContent.getContentTitle() << "`" << singleContent.getContentAuthor() << "`";
			const std::vector<std::string>& singleContentKW = singleContent.getContentKeyWords();
			for (size_t j = 0; j < singleContentKW.size(); ++j) {
				ofs << singleContentKW[j];
				if (j != singleContentKW.size() - 1)
					ofs << "^";
			}
			if (i != contents.size() - 1)
				ofs << "|";
		}
	}

	ofs << std::endl;
	ofs.close();
}

void Series::saveAllToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open() || !ofs.good())
		throw std::runtime_error("Something wrong with stream - it is either bad or it can't be opened\n");

	ofs << getID() << "," << getTitle() << "," << getPublisher() << "," << getGenre() << ","
		<< getDescription() << "," << getYearPublished() << "," << getRating();

	ofs << "," << static_cast<int>(getMonthPublished()) << ","
		<< getCount() << ","
		<< getISSN() << ",";

	ofs << getAuthor() << ",";

	const std::vector<std::string>& kws = getKeyWords();
	for (size_t i = 0; i < kws.size(); ++i) {
		ofs << kws[i];
		if (i != kws.size() - 1)
			ofs << "~";
	}
	ofs << ",";

	ofs << getISBN();

	const std::vector<Contents>& contents = getContent();
	if (!contents.empty()) {
		ofs << "|";
		for (size_t i = 0; i < contents.size(); ++i) {
			const Contents& singleContent = contents[i];
			ofs << singleContent.getContentTitle() << "`" << singleContent.getContentAuthor() << "`";
			const std::vector<std::string>& singleContentKW = singleContent.getContentKeyWords();
			for (size_t j = 0; j < singleContentKW.size(); ++j) {
				ofs << singleContentKW[j];
				if (j != singleContentKW.size() - 1)
					ofs << "^";
			}
			if (i != contents.size() - 1)
				ofs << "|";
		}
	}

	ofs << std::endl;
}

std::string Series::getType() const
{
	return "Series";
}

Series* Series::loadFromFile(const std::string& line)
{
	size_t sep = line.find('|');
	if (sep == std::string::npos)
		throw std::runtime_error("Invalid series format: missing '|'");

	std::vector<std::string> beforePipe = split(line.substr(0, sep), ',');
	if (beforePipe.size() < 13)
		throw std::runtime_error("Invalid series metadata format");

	std::vector<std::string> afterPipe = split(line.substr(sep + 1), '|');

	unsigned id = parseToInt(beforePipe[0]);
	std::string title = beforePipe[1];
	std::string publisher = beforePipe[2];
	std::string genre = beforePipe[3];
	std::string description = beforePipe[4];
	int yearPublished = parseToInt(beforePipe[5]);
	double rating = std::stod(beforePipe[6]);  // ако rating е double
	int monthPublished = parseToInt(beforePipe[7]);
	int count = parseToInt(beforePipe[8]);
	std::string ISSN = beforePipe[9];
	std::string author = beforePipe[10];
	std::vector<std::string> keyWords = split(beforePipe[11], '~');
	std::string ISBN = beforePipe[12];

	std::vector<Contents> parsedContents;
	for (const std::string& content : afterPipe) {
		std::vector<std::string> parts = split(content, '`');
		if (parts.size() != 3)
			throw std::runtime_error("Invalid content format in series");

		std::string cTitle = parts[0];
		std::string cAuthor = parts[1];
		std::vector<std::string> cKeywords = split(parts[2], '^');
		parsedContents.emplace_back(cTitle, cAuthor, cKeywords);
	}

	Series* s = new Series(author, title, publisher, genre, description,
		yearPublished, monthPublished, count, keyWords, rating, ISBN.c_str(), ISSN.c_str(), parsedContents);

	return s;
}