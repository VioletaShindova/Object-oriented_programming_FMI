#pragma once
#include "Command.h"
#include "Library.h"
#include "UserFactory.h"

class AddUserCommand : public Command
{
public:
	AddUserCommand(const std::string& username, const std::string& password, bool isAdmin, Library& lib);

	void execute() const override;
	bool isExcutable() const override;
	bool userExists() const;
private:
	std::string username, password;
	bool isAdmin;
};

