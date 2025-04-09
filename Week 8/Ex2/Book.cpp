#include "Book.h"

int Book::counter = 0;

Book::Book() : Book("", "") {}

Book::Book(const char* title, const char* author) : id(counter), isFree(true) {
	setTitle(title);
	setAuthor(author);
}

Book::Book(const Book& other) : id(other.id), isFree(other.isFree), user(other.user) {
	copyDynamic(other);
}

Book& Book::operator=(const Book& other) {
	if (this != &other) {
		this->id = other.id;
		this->isFree = other.isFree;
		this->user = other.user;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Book::~Book() {
	freeDynamic();
}

void Book::assignId() {
	this->id = counter++;
}

size_t Book::getId() const {
	return this->id;
}

const char* Book::getTitle() const {
	return this->title;
}

const char* Book::getAuthor() const {
	return this->author;
}

bool Book::getStatus() const {
	return this->isFree;
}

void Book::print() const {
	std::cout << "Id: " << this->id << " Title: " << this->title
		<< " Author: " << this->author << " Status: " << this->isFree << std::endl;
}

void Book::setTakenByWho(const User& user) {
	this->isFree = false;
	this->user = user;
}

void Book::setFree() {
	this->isFree = true;
	this->user = User("", "");
}

void Book::setTitle(const char* title) {
	if (!title)
		throw std::invalid_argument("Invalid name!");

	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
}

void Book::setAuthor(const char* author) {
	if (!author)
		throw std::invalid_argument("Invalid name!");

	this->author = new char[strlen(author) + 1];
	strcpy(this->author, author);
}

void Book::copyDynamic(const Book& other) {
	title = new char[strlen(other.title) + 1];
	strcpy(title, other.title);

	author = new char[strlen(other.author) + 1];
	strcpy(author, other.author);
}

void Book::freeDynamic() {
	delete[] title;
	delete[] author;
}