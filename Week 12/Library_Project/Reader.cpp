#include "Reader.h"


Reader::Reader(const std::string& username, const std::string& password) : User(username, password) {}

Reader::Reader(const std::string& username, const std::string& password, const std::chrono::year_month_day& registrationDate, std::time_t lastLoginTime, const std::vector<ItemRecord>& items)
	: User(username, password)
{
	ymd = registrationDate;
	setLastLogInDate();
	setItems(items);
}

void Reader::setItems(const std::vector<ItemRecord>& items)
{
}

bool Reader::isAdmin() const
{
	return false;
}

User* Reader::clone() const
{
	return new Reader(*this);
}

void Reader::print(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Invalid stream\n");

	User::print(os);

	for (size_t i = 0; i < items.size(); i++)
		items[i].print(os);
}

std::vector<Reader::ItemRecord>& Reader::getTakenItems() noexcept
{
	return items;
}

/*
std::string username;
	std::string password;
	std::chrono::year_month_day ymd; //includes only year, month and day
	mutable std::time_t lastLogInDate; //includes date and time
*/

void Reader::saveAllToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open() || !ofs.good())
		throw std::runtime_error("Something wrong with stream - it is either bad or it can't be opened\n");

	ofs << getUsername() << "," << getPassword() << "," << getYMD() << "," << getLastLogInDate();

	for (size_t i = 0; i < items.size(); ++i) {
		ofs << "|";
		items[i].saveAllToFile(ofs);
	}

	ofs << std::endl;
}

std::string Reader::getType() const
{
	return "Reader";
}

Reader::ItemRecord Reader::ItemRecord::fromSerialized(unsigned itemID, std::time_t taken, std::time_t returned, bool isReturned)
{
	ItemRecord record(itemID, 0); // daysUntilReturn няма значение тук
	record.itemIsTakenOnDate = taken;
	record.itemToBeReturnedOnDate = returned;
	record.itemIsReturned = isReturned;
	return record;
}

Reader* Reader::loadFromFile(const std::string& line)
{
	std::vector<std::string> parts = split(line, ',');

	if (parts.size() < 4)
		throw std::runtime_error("Invalid Reader data");

	const std::string username = parts[0];
	const std::string password = parts[1];
	const std::chrono::year_month_day ymd = parseDate(parts[2]);
	const std::time_t lastLogin = static_cast<std::time_t>(std::stoll(parts[3]));

	std::vector<ItemRecord> itemRecords;

	for (size_t i = 4; i < parts.size(); ++i) {
		std::vector<std::string> itemParts = split(parts[i], '~');
		if (itemParts.size() != 4)
			throw std::runtime_error("Invalid ItemRecord format");

		unsigned itemID = static_cast<unsigned>(std::stoul(itemParts[0]));
		std::time_t taken = static_cast<std::time_t>(std::stoll(itemParts[1]));
		std::time_t returned = static_cast<std::time_t>(std::stoll(itemParts[2]));
		bool isReturned = (itemParts[3] == "1");

		ItemRecord record = ItemRecord::fromSerialized(itemID, taken, returned, isReturned);
		itemRecords.push_back(record);
	}

	return new Reader(username, password, ymd, lastLogin, itemRecords);
}

Reader::ItemRecord::ItemRecord(unsigned itemId, int daysUntilReturn) : itemID(itemId)
{
	setItemIsTakenOnDate();
	setItemToBeReturnedOnDate(daysUntilReturn);

}

void Reader::ItemRecord::setItemToBeReturnedOnDate(int daysUntilReturn)
{
	std::time_t now = std::time(nullptr);
	itemToBeReturnedOnDate = now + (daysUntilReturn * 24 * 60 * 60);
}

void Reader::ItemRecord::setItemIsReturned()
{
	std::time_t now = std::time(nullptr);
	itemIsReturned = (now > itemToBeReturnedOnDate); //item is returned
}

unsigned Reader::ItemRecord::getItemID() const noexcept
{
	return itemID;
}

const std::time_t& Reader::ItemRecord::getItemIsTakenOnDate() const noexcept
{
	return itemIsTakenOnDate;
}

const std::time_t& Reader::ItemRecord::getItemIsReturnedOnDate() const noexcept
{
	return itemToBeReturnedOnDate;
}

bool Reader::ItemRecord::getItemIsReturned() const noexcept
{
	return itemIsReturned;
}

std::time_t& Reader::ItemRecord::getItemIsTakenOnDate() noexcept
{
	return itemIsTakenOnDate;
}

std::time_t& Reader::ItemRecord::getItemIsReturnedOnDate() noexcept
{
	return itemToBeReturnedOnDate;
}

bool& Reader::ItemRecord::getItemIsReturned() noexcept
{
	return itemIsReturned;
}

bool Reader::ItemRecord::checkIfItemIsReturned() const noexcept
{
	return itemIsReturned == true;
}

const std::time_t Reader::ItemRecord::getDaysLeftUntilReturn() const
{
	return itemToBeReturnedOnDate - itemIsTakenOnDate;
}

void Reader::ItemRecord::print(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Invalid stream\n");

	os << itemID << ' ' << formatTimeYYMMDDhhmmss(itemIsTakenOnDate) << ' ' << formatTimeYYMMDDhhmmss(itemToBeReturnedOnDate) << ' ' << ((itemIsReturned) ? "Yes" : "No") << '\n';
}

void Reader::ItemRecord::saveAllToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open() || !ofs.good())
		throw std::runtime_error("Something wrong with stream - it is either bad or it can't be opened\n");

	ofs << itemID << "~" << itemIsTakenOnDate << "~" << itemToBeReturnedOnDate << "~" << itemIsReturned;
}

void Reader::ItemRecord::setItemIsTakenOnDate()
{
	itemIsTakenOnDate = std::time(nullptr); //returns the second that passed from 1 January, 1970 until now
}
