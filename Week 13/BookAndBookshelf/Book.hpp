#pragma once

#ifndef __BOOK_HEADER_INCLUDED_
#define __BOOK_HEADER_INCLUDED_

#include <iostream>

namespace GlobalConstants {
	constexpr size_t ID_SIZE = 11;
	constexpr size_t MAX_VALUE_BOOKS = 500;
}

class Book
{
public:
	Book();
	Book(const char* name, const char* author, int pages);

	Book(const Book& other);
	Book& operator=(const Book& other) = delete;

	~Book() noexcept;

	void setName(const char* name);
	void setAuthor(const char* author);

	inline const char* getName() const noexcept { return name; }
	inline const char* getAuthor() const noexcept { return author; }
	inline unsigned getPages() const noexcept { return pages; }
	inline const char* getID() const noexcept { return id; }

	bool writeToStream(std::ostream& os) const;
	bool readFromStream(std::istream& is);

private:
	void setPages(int pages);
	void formatID();
	void copyDynamic(const Book& other);
	void freeDynamic();
	static unsigned incrementID();

	char* name;
	char* author;
	unsigned pages;
	char id[GlobalConstants::ID_SIZE + 1] = "IS-INF-0000";

	unsigned currID;
	static unsigned lastID;
};

bool areEqual(const Book* lhs, const Book* rhs);

#endif