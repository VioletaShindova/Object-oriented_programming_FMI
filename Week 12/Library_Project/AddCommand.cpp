#include "AddCommand.h"

AddUserCommand::AddUserCommand(const std::string& username, const std::string& password, bool isAdmin, Library& lib)
	: Command(lib), username(username), password(password), isAdmin(isAdmin) {}

void AddUserCommand::execute() const
{
	if (!lib.isSomeoneLogged()) {
		throw std::logic_error("Only admins can do that. No one is logged\n");
	}
	else if (!lib.getCurrentLoggedUser()->isAdmin()) {
		throw std::logic_error("You are not admin! Only admins can do that.\n");
	}
	else if (userExists()) {
		throw std::logic_error("User already exists\n");
	}
	else 
	{
		User* newUser = UserFactory::createUser(username, password, isAdmin);
		lib.addUser(newUser);
	}
}

bool AddUserCommand::isExcutable() const
{
	return false;
}

bool AddUserCommand::userExists() const
{
	const std::vector<User*> users = lib.getUsers();
	size_t usersCount = users.size();
	for (size_t i = 0; i < usersCount; i++)
	{
		if (username == users[i]->getUsername())
			return true;
	}
	return false;
}


