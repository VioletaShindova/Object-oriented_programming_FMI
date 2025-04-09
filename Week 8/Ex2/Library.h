#pragma once
#include "Book.h"
#include "User.h"

constexpr size_t MAX_SIZE_BOOK = 50;

class Library
{
public:
	Library();

	Library(const Book* books, int size);

	const Book* getBooks() const;

	void print() const;

	bool addBook(const Book& book);

	bool makeBookTakenBy(size_t id, const User& userName);

	bool makeBookFree(size_t id);

private:
	void setBooks(const Book* books, int size);

	bool areValidBooks(const Book* books, int size) const;

	Book books[MAX_SIZE_BOOK];
	size_t currSize;
};

