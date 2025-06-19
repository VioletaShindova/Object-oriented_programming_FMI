#include "PrintCommand.h"

PrintCommand::PrintCommand(Library& lib, const std::string& fileName) : Command(lib)
{
	setFileName(fileName);
}

void PrintCommand::execute() const
{	
	lib.print(fileName);
}

bool PrintCommand::isExcutable() const
{
	return true;
}

void PrintCommand::setFileName(const std::string& fileName)
{
	if (fileName.empty())
		throw std::invalid_argument("Invalid file name\n");

	this->fileName = fileName;
}
