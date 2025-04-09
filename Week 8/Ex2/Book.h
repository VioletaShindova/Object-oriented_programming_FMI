#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include "User.h"

class Book
{
public:
	Book();

	Book(const char* title, const char* author);

	Book(const Book& other);

	Book& operator=(const Book& other);

	~Book();

	void assignId();

	size_t getId() const;

	const char* getTitle() const;

	const char* getAuthor() const;

	bool getStatus() const;

	void print() const;

	void setTakenByWho(const User& user);

	void setFree();

private:
	void setTitle(const char* title);

	void setAuthor(const char* author);

	void copyDynamic(const Book& other);

	void freeDynamic();

	size_t id;
	char* title;
	char* author;
	bool isFree;
	User user;
	static int counter;
};

