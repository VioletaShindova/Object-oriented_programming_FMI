#pragma once
#include <string>
#include <chrono>

class User
{
public:
	User() = delete;
	User(const std::string& username, const std::string& password);

	virtual ~User() noexcept = default;

	virtual User* clone() const = 0;

	void setUsername(const std::string& username);

	void setPassword(const std::string& password);

	const std::string& getUsername() const noexcept;

	const std::string& getPassword() const noexcept;

	const std::chrono::year_month_day& getYMD() const noexcept;
	const std::time_t& getLastLogInDate() const noexcept;

	void setLastLogInDate() const;

	virtual bool isAdmin() const = 0;

	virtual void print(std::ostream& os) const;

	//friend std::ostream& operator<<(std::ostream& os, const User& user);

protected:
	void setYMD();

private:
	std::string username;
	std::string password;
	std::chrono::year_month_day ymd; //includes only year, month and day
	mutable std::time_t lastLogInDate; //includes date and time
};

