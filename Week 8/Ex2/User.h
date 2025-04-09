#pragma once

constexpr size_t MAX_SIZE_USER_NAME = 9;
constexpr size_t MAX_SIZE_USER_NUMBER = 11;

class User
{
public:
	User();

	User(const char* name, const char* number);

	void setName(const char* name);
	
	void setNumber(const char* number);

	const char* getName() const;

	const char* getNumber() const;

	void print() const;

private:
	bool isValidStr(const char* str, int len) const;

	char userName[MAX_SIZE_USER_NAME];
	char number[MAX_SIZE_USER_NUMBER];
};

