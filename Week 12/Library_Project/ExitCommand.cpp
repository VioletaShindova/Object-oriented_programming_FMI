#include "ExitCommand.h"

ExitCommand::ExitCommand(Library& lib) : Command(lib) {}

void ExitCommand::execute() const
{
    throw std::string("Exiting program...");
}

bool ExitCommand::isExcutable() const
{
    return true;
}
