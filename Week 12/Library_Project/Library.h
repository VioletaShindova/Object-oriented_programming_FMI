#pragma once
#include "User.h"
#include "Administrator.h"
#include "Item.h"
#include "Book.h"
#include "Periodical.h"
#include "Series.h"
#include <vector>
#include "Command.h" //or in cpp
#include "CommandFactory.h"
#include "HelperFunctions.h"
#include <fstream>

class Library
{
public:
	Library();
	Library(const std::vector<User*>& users, const std::vector<Item*>& items);

	const std::vector<User*>& getUsers() const noexcept;
	const std::vector<Item*>& getItems() const noexcept;

	const User* getCurrentLoggedUser() const noexcept;

	bool isSomeoneLogged() const;

	void run();

	void login(const User* user);
	void logout();
	
	void addUser(User* newUser);
	void addItem(Item* newItem);

	void print(const std::string& fileName) const;
	//void print(const std::string& fileName, const std::string& isbnOrIssn) const;

	//void read(const std::string& fileName);

	Item* getInfoOfItem(const std::string& fileName, const std::string& isbnOrIssn);

	std::vector<Item*> getItemsFromFile(const std::string& filename) const;
private:
	std::vector<User*> users;
	std::vector<Item*> items;

	const User* currentLoggedUser;
};

