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

	// Periodical (monthPublished, count, ISSN)
	ofs << "," << static_cast<int>(getMonthPublished()) << ","
		<< getCount() << ","
		<< getISSN() << ",";

	// author of Book
	ofs << getAuthor() << ",";

	// keywords of Book, separated with ~
	const std::vector<std::string>& kws = getKeyWords();
	for (size_t i = 0; i < kws.size(); ++i) {
		ofs << kws[i];
		if (i != kws.size() - 1)
			ofs << "~";
	}
	ofs << ",";

	// ISBN of Book
	ofs << getISBN();

	// Contents of periodical
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
