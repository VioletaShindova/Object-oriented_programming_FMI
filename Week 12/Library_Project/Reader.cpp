#include "Reader.h"


Reader::Reader(const std::string& username, const std::string& password) : User(username, password) {}

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

void Reader::ItemRecord::setItemIsTakenOnDate()
{
	itemIsTakenOnDate = std::time(nullptr); //returns the second that passed from 1 January, 1970 until now
}
