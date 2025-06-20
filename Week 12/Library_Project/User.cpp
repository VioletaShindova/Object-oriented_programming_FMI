#include "User.h"
#include "HelperFunctions.h"

User::User(const std::string& username, const std::string& password)
{
	setUsername(username);
	setPassword(password);
	setYMD();
	setLastLogInDate();
}

void User::setUsername(const std::string& username)
{
	if (username.empty())
		throw std::invalid_argument("Empty username\n");

	this->username = username;
}

void User::setPassword(const std::string& password)
{
	if (password.empty())
		throw std::invalid_argument("Empty password\n");

	this->password = password;
}

const std::string& User::getUsername() const noexcept
{
	return username;
}

const std::string& User::getPassword() const noexcept
{
	return password;
}

const std::chrono::year_month_day& User::getYMD() const noexcept
{
	return ymd;
}

const std::time_t& User::getLastLogInDate() const noexcept
{
	return lastLogInDate;
}

std::time_t& User::getLastLogInDate() noexcept
{
	return lastLogInDate;
}

void User::setYMD()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	
	ymd = floor<std::chrono::days>(now);

}

void User::setLastLogInDate() const
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	this->lastLogInDate = std::chrono::system_clock::to_time_t(now);
}

void User::print(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Invalid stream\n");

	os << username << ' ' << password << ' ' << ymd << ' ' << formatTimeYYMMDDhhmmss(lastLogInDate) << ' ';
}
