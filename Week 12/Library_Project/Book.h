#pragma once
#include "Item.h"
#include <fstream>
#include <string>
#include <vector>

namespace GlobalConstants {
	constexpr size_t SIZE_ISBN = 17; //13 digits and 4 '-' since 2007 to this day
}

class Book : virtual public Item
{
public:
	Book();

	Book(const std::string& author, const std::vector<std::string>& keyWords, const char* ISBN);

	Book(const std::string& title, const std::string& publisher,
		const std::string& genre, const std::string& description,
		int yearPublished, int rating, const std::string& author,
		std::vector<std::string> keyWords, const char* ISBN);

	Book(const Item& obj, const std::string& author,
		std::vector<std::string> keyWords, const char* ISBN);

	void setAuthor(const std::string& author);
	void setKeyWords(const std::vector<std::string>& keyWords);
	void setISBN(const char* ISBN);

	const std::string& getAuthor() const noexcept;
	const std::vector<std::string>& getKeyWords() const noexcept;
	const char* getISBN() const noexcept;

	Item* clone() const override;
	void print() const override;

	void saveToFile(const std::string& fileName) const;

private:
	std::string author;
	std::vector<std::string> keyWords;
	char ISBN[GlobalConstants::SIZE_ISBN + 1];
};

