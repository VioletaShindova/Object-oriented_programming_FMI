#include "LogoutCommand.h"

LogoutCommand::LogoutCommand(Library& lib) : Command(lib) {}

void LogoutCommand::execute() const
{
	if (!isExcutable())
		throw std::logic_error("There is no current logged in user\n");
	else {
		lib.logout();
	}
}

bool LogoutCommand::isExcutable() const
{
	return lib.isSomeoneLogged();
}
