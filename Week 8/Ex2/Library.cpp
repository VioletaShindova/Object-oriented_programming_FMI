#include "Library.h"

Library::Library() : Library({}, 0) {}

Library::Library(const Book* books, int size) {
	setBooks(books, size);
}

const Book* Library::getBooks() const {
	return this->books;
}

void Library::print() const {
	for (size_t i = 0; i < this->currSize; i++)
		books[i].print();
}

bool Library::addBook(const Book& book) {
	if (this->currSize >= MAX_SIZE_BOOK)
		return false;

	Book newBook = book;
	newBook.assignId();
	books[currSize++] = newBook;
	return true;
}

bool Library::makeBookTakenBy(size_t id, const User& user) {
	for (size_t i = 0; i < this->currSize; i++) {
		if (id == books[i].getId()) {
			if (books[i].getStatus() == false)
				throw std::invalid_argument("Book is already taken!");
			books[i].setTakenByWho(user);
			return true;
		}
	}
	return false;
}

bool Library::makeBookFree(size_t id) {
	for (size_t i = 0; i < this->currSize; i++) {
		if (id == books[i].getId()) {
			if (books[i].getStatus() == true)
				throw std::invalid_argument("Book is already free!");
			books[i].setFree();
			return true;
		}
	}
	return false;
}

void Library::setBooks(const Book* books, int size) {
	if (!areValidBooks(books, size))
		throw std::invalid_argument("Invalid size!");

	this->currSize = size;
	for (size_t i = 0; i < size; i++)
		this->books[i] = books[i];
}

bool Library::areValidBooks(const Book* books, int size) const {
	return (0 <= size) && (size <= MAX_SIZE_BOOK);
}
