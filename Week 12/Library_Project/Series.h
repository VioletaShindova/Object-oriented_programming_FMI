#pragma once
#include "Periodical.h"
#include "Book.h"
#include "HelperFunctions.h"
#include <string>
#include <vector>

class Series : public Book, public Periodical
{
public:
	Series();
	Series(const std::string& author, const std::string& title, const std::string& publisher, 
		   const std::string& genre, const std::string& description, 
		int yearPublished, int monthPublished, int count, const std::vector<std::string>& keyWords, 
		double rating, const char* ISBN, const char* ISSN, const std::vector<Periodical::Contents>& content);

	void print() const override;

	Item* clone() const override;

	void saveToFile(const std::string& fileName) const override;

	void saveAllToFile(std::ofstream& ofs) const override;

	std::string getType() const override;

	static Series* loadFromFile(const std::string& line);
private:
};

