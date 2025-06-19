//#include "FindUserCommand.h"
//
//FindUserCommand::FindUserCommand(Library& lib, const std::string& option, const std::string& value) : Command(lib), option(option), value(value) {}
//
//void FindUserCommand::findByName() const
//{
//	const std::vector<User*>& users = lib.getUsers();
//	for (size_t i = 0; i < users.size(); ++i) {
//		if (users[i]->getUsername() == value) {
//			users[i]->print(std::cout);
//			return;
//		}
//	}
//	std::cout << "No user found with name: " << value << std::endl;
//}
//
//void FindUserCommand::findByItemID() const
//{
//	const std::vector<User*>& users = lib.getUsers();
//	bool found = false;
//
//	for (size_t i = 0; i < users.size(); ++i) {
//		Reader* reader = dynamic_cast<Reader*>(users[i]);
//
//		if (!reader) 
//			continue;
//
//		const auto& items = reader->getTakenItems();
//		for (size_t j = 0; j < items.size(); ++j) {
//			if (items[j].getItem()->getID() == value) {
//				reader->print(std::cout);
//				found = true;
//				break;
//			}
//		}
//	}
//	if (!found)
//		std::cout << "No user found with item ID: " << value << std::endl;
//}
//
//
//
//void FindUserCommand::findByState() const
//{
//	if (value == "overdue") {
//		findOverdueUsers();
//	}
//	else if (value == "reader") {
//		findActiveReaders();
//	}
//	else if (value == "inactive") {
//		findInactiveUsers();
//	}
//	else {
//		std::cout << "Invalid state value: " << value << std::endl;
//	}
//}
//
//void FindUserCommand::findOverdueUsers() const
//{
//	const std::vector<User*> users = lib.getUsers();
//	bool found 
//}
//
//void FindUserCommand::execute() const
//{
//	if (option == "name") {
//		findByName();
//	}
//	else if (option == "ID") {
//		findByItemID();
//	}
//	else if (option == "state") {
//		findByState();
//	}
//	else {
//		std::cout << "Invalid option: " << option << std::endl;
//	}
//}
//
//bool FindUserCommand::isExcutable() const
//{
//	return lib.isSomeoneLogged();
//}
//
