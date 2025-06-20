#pragma once
#include "Item.h"
#include "HelperFunctions.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#pragma warning(disable : 4996)

namespace GlobalConstants {
	constexpr size_t SIZE_ISSN = 9; //1314-1237 or 0040-781X
}

enum class Month {
	INVALID,
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
	COUNT
};

class Periodical : virtual public Item
{
public:
	struct Contents {
	public:
		Contents() = default;

		Contents(const std::string& contentTitle, const std::string& contentAuthor,
				 const std::vector<std::string>& contentKeyWords);

		void setContentTitle(const std::string& contentTitle);
		void setContentAuthor(const std::string& contentAuthor);
		void setContentKeyWords(const std::vector<std::string>& contentKeyWords);

		const std::string& getContentTitle() const noexcept;

		const std::string& getContentAuthor() const noexcept;

		const std::vector<std::string>& getContentKeyWords() const noexcept;

		void print() const;

	private:

		std::string contentTitle = "unknown title content";
		std::string contentAuthor = "unknown author of content";
		std::vector<std::string> contentKeyWords = {};
	};

	Periodical();

	Periodical(int monthPublished, int count, const char* ISSN, const std::vector<Contents>& content);

	Periodical(const std::string& title, const std::string& publisher,
		const std::string& genre, const std::string& description,
		int yearPublished, int rating, int monthPublished, int count, const char* ISSN, 
		const std::vector<Contents>& content);

	Periodical(const Item& obj, int monthPublished, int count, const char* ISSN, const std::vector<Contents>& content);

	void setMonthPublished(int monthPublished);

	void setCount(int count);

	void setISSN(const char* ISSN);

	void setContent(const std::vector<Contents>& content);

	Month getMonthPublished() const noexcept;

	size_t getCount() const noexcept;

	const char* getISSN() const noexcept;

	const std::vector<Contents>& getContent() const noexcept;

	void print() const override;

	Item* clone() const override;

	void saveToFile(const std::string& fileName) const override;

	void saveAllToFile(std::ofstream& ofs) const override;

	std::string getType() const override;

	static Periodical* loadFromFile(const std::string& line);

private:
	bool isValidMonth(int monthPublished) const;
	bool isValidISSN(const char* ISSN) const;
	
	Month monthPublished;
	size_t count; //брой периодично издание
	char ISSN[GlobalConstants::SIZE_ISSN + 1];
	std::vector<Contents> content;
};

