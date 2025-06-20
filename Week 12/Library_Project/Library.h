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
	//don't check in files
	Library();
	Library(const std::vector<User*>& users, const std::vector<Item*>& items);
	Library(const Library& other);
	Library& operator=(const Library& other);
	~Library();

	void setUsers(const std::vector<User*>& users);
	void setItems(const std::vector<Item*>& items);

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

	void serialize() const;

	void deserialize();

	//must be a template func
	std::vector<Item*> getOnlyOneTypeOfItem(const std::string& typeItem) const;
	std::vector<User*> getOnlyOneTypeOfUser(const std::string& typeUser) const;

private:
	void copyDynamic(const Library& other);
	void freeDynamic();
	std::vector<User*> users;
	std::vector<Item*> items;

	User* currentLoggedUser;
};