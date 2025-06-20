#pragma once
#include "User.h"
#include "Item.h"
#include "HelperFunctions.h"
#include <vector>

class Reader : public User
{
public:
	struct ItemRecord {
	public:
		ItemRecord() = default;
		ItemRecord(unsigned itemId, int daysUntilReturn);

		void setItemToBeReturnedOnDate(int daysUntilReturn);
		void setItemIsReturned();

		unsigned getItemID() const noexcept;
		const std::time_t& getItemIsTakenOnDate() const noexcept;
		const std::time_t& getItemIsReturnedOnDate() const noexcept;
		bool getItemIsReturned() const noexcept;

		std::time_t& getItemIsTakenOnDate() noexcept;
		std::time_t& getItemIsReturnedOnDate() noexcept;
		bool& getItemIsReturned() noexcept;

		bool checkIfItemIsReturned() const noexcept;

		const std::time_t getDaysLeftUntilReturn() const;

		void print(std::ostream& os) const;

		void saveAllToFile(std::ofstream& ofs) const;

		static ItemRecord fromSerialized(unsigned itemID, std::time_t taken, std::time_t returned, bool isReturned);

	private:
		void setItemIsTakenOnDate();

		unsigned itemID;
		std::time_t itemIsTakenOnDate;
		std::time_t itemToBeReturnedOnDate;
		bool itemIsReturned = false;
	};

	Reader() = delete;
	Reader(const std::string& username, const std::string& password);
	Reader(const std::string& username, const std::string& password, const std::chrono::year_month_day& registrationDate, std::time_t lastLoginTime, const std::vector<ItemRecord>& items);

	void setItems(const std::vector<ItemRecord>& items);
	//void addItem(const ItemRecord& item); must implement

	bool isAdmin() const override;
	User* clone() const override;
	void print(std::ostream& os) const override;

	std::vector<ItemRecord>& getTakenItems() noexcept;

	void saveAllToFile(std::ofstream& ofs) const override;

	std::string getType() const override;

	static Reader* loadFromFile(const std::string& line);

private:
	std::vector<ItemRecord> items = {};
};

