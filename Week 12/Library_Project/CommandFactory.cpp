#include "CommandFactory.h"

static std::string extractValue(const std::vector<std::string>& splittedCommand, size_t& index)
{
	std::string value;

	while (index < splittedCommand.size() && splittedCommand[index] != "sort" && splittedCommand[index] != "top")
	{
		value += splittedCommand[index++] + " ";
	}
	if (!value.empty())
		value.pop_back(); //we pop back the last space " "

	return value;
}

static void extractSortAndTopOptions(const std::vector<std::string>& splittedCommand, size_t index, std::string& sortKey, bool& ascending, int& top)
{
	if (index < splittedCommand.size() && splittedCommand[index] == "sort") {
		if (++index < splittedCommand.size()) {
			sortKey = splittedCommand[index++];
			if (index < splittedCommand.size()) {
				if (splittedCommand[index] == "desc") {
					ascending = false;
					++index;
				}
				else if (splittedCommand[index] == "asc") {
					ascending = true;
					++index;
				}
			}
		}
		else {
			throw std::runtime_error("Missing key after 'sort'.");
		}
	}

	if (index < splittedCommand.size() && splittedCommand[index] == "top") {
		if (++index < splittedCommand.size()) {
			top = parseToInt(splittedCommand[index]);
		}
		else {
			throw std::runtime_error("Missing value after 'top'.");
		}
	}
}

static std::string determineFile(const std::string& category) {
	if (category == "books")
		return "books.txt";
	else if (category == "series")
		return "series.txt";
	else if (category == "newsletters")
		return "newsletters.txt";
	else if (category == "list")
		return "items.txt";
	else
		throw std::runtime_error("Invalid category for find command.");
}
//--------------------------------------------------------------------------------------------------------
Command* CommandFactory::createCommand(const std::string& command, Library& lib)
{
	if (command == "help") {
		return new HelpCommand(lib);
	}
	else if (command == "exit") {
		return new ExitCommand(lib);
	}
	else if (command == "login") {

		std::cout << "Enter username: ";
		std::string username = readLine(std::cin);
			
		std::cout << "Enter password: ";
		std::string password = readLine(std::cin);

		return new LoginCommand(username, password, lib);
	}
	else if (command == "logout") {
		return new LogoutCommand(lib);
	}
	else if (isPrefix(command, "user add")) {

		std::vector<std::string> splittedCommand = split(command, ' '); //must think whether username contains ' ' 

		if (splittedCommand.size() == 4)
			return new AddUserCommand(splittedCommand[2], splittedCommand[3], false, lib);
		else if (splittedCommand.size() == 5 && splittedCommand[4] == "admin") {
			return new AddUserCommand(splittedCommand[2], splittedCommand[3], true, lib);
		}
	}
	else if (command == "users all") {
		return new PrintCommand(lib, lib.getUsers());
	}
	else if (command == "books all") {
		return new PrintCommand(lib, lib.getOnlyOneTypeOfItem("Book"));
	}
	else if (command == "newsletters all") {
		return new PrintCommand(lib, lib.getOnlyOneTypeOfItem("Periodical"));
	}
	else if (command == "series all") {
		return new PrintCommand(lib, lib.getOnlyOneTypeOfItem("Series"));
	}
	else if (command == "list all") {
		return new PrintCommand(lib, lib.getItems());
	}
	else if (isPrefix(command, "list info")) {
		std::vector<std::string> splittedCommand = split(command, ' ');

		if (splittedCommand.size() != 3) {
			std::cout << "Invalid syntax. Use: list info <isbn/issn>\n";
			return nullptr;
		}

		const std::string isbnOrIssn = splittedCommand[2];
		return new InfoCommand(lib, isbnOrIssn);
	}
	else if (isPrefix(command, "books find") ||
		isPrefix(command, "series find") ||
		isPrefix(command, "newsletters find") ||
		isPrefix(command, "list find")) {

		std::vector<std::string> splittedCommand = split(command, ' ');

		if (splittedCommand.size() < 4) {
			std::cout << "Invalid find syntax.\n";
			return nullptr;
		}

		const std::string& category = splittedCommand[0];
		const std::string& option = splittedCommand[2];

		size_t index = 3;
		std::string value = extractValue(splittedCommand, index);
	
		std::string sortKey;
		bool ascending = true;
		int top = -1;

		try {
			extractSortAndTopOptions(splittedCommand, index, sortKey, ascending, top);
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			return nullptr;
		}

		std::string file = "";
		try {
			file = determineFile(category);
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			return nullptr;
		}

		return new FindCommand(lib, file, option, value, sortKey, ascending, top);
	}
	//else if (isPrefix(command, "user find"))
	//{
	//	std::vector<std::string> splittedCommand = split(command, ' ');

	//	if (splittedCommand.size() < 4) {
	//		std::cout << "Invalid syntax. Use: user find <option> <option_string>\n";
	//		return nullptr;
	//	}

	//	std::string option = splittedCommand[2];
	//	std::string value;

	//	for (size_t i = 3; i < splittedCommand.size(); ++i) {
	//		value += splittedCommand[i];
	//		if (i != splittedCommand.size() - 1)
	//			value += " ";
	//	}

	//	if (option != "name" && option != "ID" && option != "state") {
	//		std::cout << "Invalid option. Must be one of: name, ID, state.\n";
	//		return nullptr;
	//	}

	//	if (option == "state" && value != "overdue" && value != "reader" && value != "inactive") {
	//		std::cout << "Invalid state value. Must be: overdue, reader, or inactive.\n";
	//		return nullptr;
	//	}

	//	return new FindUserCommand(lib, option, value);
	//}
	else if (command == "books add") {
		return new AddBookCommand(lib);
	}
	else if (command == "series add") {
		return new AddSeriesCommand(lib);
	}
	else if (command == "newsletters add") {
		return new AddNewsletterCommand(lib);
	}
	return nullptr;
}