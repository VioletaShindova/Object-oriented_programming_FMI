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

		bool checkIfItemIsReturned() const noexcept;

		const std::time_t getDaysLeftUntilReturn() const;

		void print(std::ostream& os) const;

	private:
		void setItemIsTakenOnDate();

		unsigned itemID;
		std::time_t itemIsTakenOnDate;
		std::time_t itemToBeReturnedOnDate;
		bool itemIsReturned = false;
	};

	Reader() = delete;
	Reader(const std::string& username, const std::string& password);

	bool isAdmin() const override;
	User* clone() const override;
	void print(std::ostream& os) const override;

	std::vector<ItemRecord>& getTakenItems() noexcept;


private:
	std::vector<ItemRecord> items = {};
};

