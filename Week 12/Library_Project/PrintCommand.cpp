#include "PrintCommand.h"

PrintCommand::PrintCommand(Library& lib, const std::vector<Item*>& items)
    : Command(lib), itemsToPrint(items), mode(Mode::FromItems) {
}

PrintCommand::PrintCommand(Library& lib, const std::vector<User*>& users)
    : Command(lib), usersToPrint(users), mode(Mode::FromUsers) {
}

PrintCommand::PrintCommand(Library& lib, const std::string& file)
    : Command(lib), mode(Mode::FromFile) 
{
    setFileName(file);
}

void PrintCommand::execute() const
{
    switch (mode) {
    case Mode::FromItems:
        for (const Item* item : itemsToPrint) {
            if (item) {
                std::cout << item->getType() << ":\n";
                item->print();  // очаква се да имаш virtual void print() const
            }
            std::cout << std::endl;
        }
        break;

    case Mode::FromUsers:
        for (const User* user : usersToPrint) {
            if (user)
                user->print(std::cout);  // ако имаш `print(std::ostream&)`
            std::cout << std::endl;
        }
        break;

    case Mode::FromFile:
        lib.print(fileName); 
        std::cout << std::endl;
        break;
    }
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
