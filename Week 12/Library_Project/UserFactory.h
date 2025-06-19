#pragma once
#include "User.h"
#include "Administrator.h"
#include "Reader.h"

class UserFactory
{
public:
	static User* createUser(const std::string& username, const std::string& password, bool isAdmin);
};

