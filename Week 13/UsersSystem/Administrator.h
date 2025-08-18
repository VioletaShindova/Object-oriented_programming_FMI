#pragma once

#ifndef __ADMINISTRATOR_HEADER_INCLUDED_

#define __ADMINISTRATOR_HEADER_INCLUDED_

#include "User.h"
#include <iostream>

class Administrator : public User
{
public:
	Administrator();
	Administrator(const char* email, const char* password, int internship = 0, int lvlOfCompetance = 1);
	Administrator(const User& user, int internship = 0, int lvlOfCompetance = 1);

	void setInternship(int internship);
	void setLevelOfCompetance(int lvlOfCompetance);

	inline unsigned getInternship() const noexcept { return internship; }
	inline unsigned getLevelOfCompetance() const noexcept { return lvlOfCompetance; }

	Administrator& operator++();
	Administrator operator++(int);

	Administrator& operator--();
	Administrator operator--(int);

	friend std::ostream& operator<<(std::ostream& os, const Administrator& other);
	friend std::istream& operator>>(std::istream& is, Administrator& other);

private:
	unsigned internship;
	unsigned lvlOfCompetance;
};

bool isValidLvlOfCompetance(int lvlOfCompetance);

bool operator<(const Administrator& lhs, const Administrator& rhs);
bool operator<=(const Administrator& lhs, const Administrator& rhs);
bool operator>(const Administrator& lhs, const Administrator& rhs);
bool operator>=(const Administrator& lhs, const Administrator& rhs);

#endif