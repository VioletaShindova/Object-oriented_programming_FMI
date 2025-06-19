#include "LoginCommand.h"

LoginCommand::LoginCommand(const std::string& username, const std::string& password, Library& lib) 
	: Command(lib), username(username), password(password)
{
}

void LoginCommand::execute() const
{
	if(lib.isSomeoneLogged())
		throw std::logic_error("You are already logged!\n");

	const User* user = getUser(username);

	if (!user)
		throw std::logic_error("No such user with this username\n");
	else {
		if (password != user->getPassword())
			throw std::logic_error("Incorrect password\n");
		else
			lib.login(user);
	}
}

bool LoginCommand::isExcutable() const
{
	return true;
}

const User* LoginCommand::getUser(const std::string& username) const
{
	const std::vector<User*> users = lib.getUsers();
	size_t usersCount = users.size();
	for (size_t i = 0; i < usersCount; i++)
	{
		if (username == users[i]->getUsername())
			return users[i];
	}
	return nullptr;
}
