#pragma once

#ifndef __SYSTEM_HEADER_INCLUDED_

#define __SYSTEM_HEADER_INCLUDED_

class User;
class Administrator;
#include <iostream>

class System
{
public:
	System();
	System(const char* name);
	System(const System& other);
	System& operator=(const System& other) = delete;
	~System() noexcept;

	inline const char* getName() const noexcept { return name; }
	inline User** getUsers() const noexcept { return users; }
	inline size_t getSize() const noexcept { return size; }

	void setName(const char* name);
	void setUsers(int capacity);
	void setUsers(User** users, int size);

	System& operator+=(const User* rhs);
	System& operator-=(const User* rhs);

	bool operator()(const Administrator* toAddAdmin);

	Administrator* operator^(int lvlOfCompetance);

	friend std::ostream& operator<<(std::ostream& os, const System& other);
	friend std::istream& operator>>(std::istream& is, System& other);

private:
	size_t getCountOfAdmins() const;
	bool existsUser(const User* toFind) const;
	bool isFoundSingleSuperUser(User** users, int size) const;
	void freeDynamic();
	void copyDynamic(const System& other);
	void resize();

	char* name;
	User** users;
	size_t size;
	size_t capacity;
};

System operator+(const System& lhs, const User* rhs);
System operator-(const System& lhs, const User* rhs);

#endif