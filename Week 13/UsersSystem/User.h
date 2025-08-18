#pragma once

#ifndef __USER_HEADER_INCLUDED_

#define __USER_HEADER_INCLUDED_

#include <iostream>

class User
{
public:
	User();
	User(const char* email, const char* password);
	User(const User& other);
	User& operator=(const User& other);
	virtual ~User() noexcept;

	void setPassword(const char* password);

	inline const char* getEmail() const noexcept { return email; }
	inline const char* getPassword() const noexcept { return password; }

	friend std::ostream& operator<<(std::ostream& os, const User& other);
	friend std::istream& operator>>(std::istream& is, User& other);

private:
	void setEmail(const char* email);
	bool isValidEmail(const char* email) const;
	void freeDynamic();
	void copyDynamic(const User& other);

	char* email; //username
	char* password;
};

bool operator==(const User& lhs, const User& rhs);
bool operator!=(const User& lhs, const User& rhs);

#endif // !__USER_HEADER_INCLUDED_