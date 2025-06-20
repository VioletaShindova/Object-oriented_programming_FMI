#include "HelpCommand.h"

HelpCommand::HelpCommand(Library& lib) : Command(lib) {}

void HelpCommand::execute() const
{
	std::cout << "List of commands:" << std::endl;
	std::cout << "> login - login to an acc" << std::endl;
	std::cout << "> logout - logout from account" << std::endl;
	std::cout << "> exit - exit the system" << std::endl;
	std::cout << "> books/newsletters/series/list all - view all books/newsletters/series/items " << std::endl;
	std::cout << "> find - find an item" << std::endl;
	std::cout << "> info - find the info of an item" << std::endl;
	std::cout << "> books/newsletters/series/user add - add new item" << std::endl;
	std::cout << "> remove - remove an item" << std::endl;
	std::cout << "> change - change an item" << std::endl;
	std::cout << "> take/return - take/return an item" << std::endl;
	std::cout << "> user add" << std::endl;
	std::cout << "> user remove" << std::endl;
	std::cout << "> user find" << std::endl;
	std::cout << "> user change" << std::endl;
}

bool HelpCommand::isExcutable() const
{
	return true;
}
