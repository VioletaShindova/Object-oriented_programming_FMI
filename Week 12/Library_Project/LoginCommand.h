#pragma once
#include "Library.h"
#include "Command.h"
#include <string>

class LoginCommand : public Command
{
public:
	LoginCommand(const std::string& username, const std::string& password, Library& lib);

	void execute() const override;
	bool isExcutable() const override;
protected:
	std::string username, password;

private:
	const User* getUser(const std::string& username) const;
};

