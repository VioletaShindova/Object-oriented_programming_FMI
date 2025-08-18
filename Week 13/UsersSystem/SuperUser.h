#pragma once

#ifndef __SUPER_USER_HEADER_INCLUDED_

#define __SUPER_USER_HEADER_INCLUDED_

#include "Administrator.h"
#include <iostream>

class SuperUser : public Administrator
{
public:
	SuperUser();
	SuperUser(const char* email, const char* password, int internship = 0, int lvlOfCompetance = 1, int capacity = 1);
	SuperUser(const User& user, int internship = 0, int lvlOfCompetance = 1, int capacity = 1);
	SuperUser(const SuperUser& other);
	SuperUser& operator=(const SuperUser& other);
	virtual ~SuperUser() noexcept override;

	void operator()();

	void setUserNames(char** usernames, int size);
	inline char** getUserNames() const noexcept { return usernames; }

	friend std::ostream& operator<<(std::ostream& os, const SuperUser& other);
	friend std::istream& operator>>(std::istream& is, SuperUser& other);

private:
	void freeDynamic();
	void copyDynamic(const SuperUser& other);
	void resize();

	char** usernames;
	size_t size;
	size_t capacity;
};

#endif