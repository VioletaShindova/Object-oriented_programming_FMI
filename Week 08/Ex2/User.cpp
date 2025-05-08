#include "User.h"
#include <iostream>
#pragma warning(disable : 4996)

User::User() : User("", "") {}

User::User(const char* name, const char* number) {
	setName(name);
	setNumber(number);
}

void User::setName(const char* name) {
	if (!isValidStr(name, MAX_SIZE_USER_NAME))
		throw std::invalid_argument("Invalid size!");

	strcpy(this->userName, name);
}

void User::setNumber(const char* number) {
	if (!isValidStr(number, MAX_SIZE_USER_NUMBER))
		throw std::invalid_argument("Invalid size!");

	strcpy(this->number, number);
}

const char* User::getName() const {
	return this->userName;
}

const char* User::getNumber() const {
	return this->number;
}

void User::print() const {
	std::cout << "Name: " << this->userName << ", number: " << this->number << std::endl;
}

bool User::isValidStr(const char* str, int len) const {
	return (str && (0 <= (strlen(str)) && strlen(str) <= len - 1));
}