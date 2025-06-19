#pragma once
#include "User.h"
#include <string>

class Administrator : public User
{
public:
	Administrator() = delete;
	Administrator(const std::string& username, const std::string& password, const std::string& email);

	void setEmail(const std::string& email);

	bool isAdmin() const override;
	User* clone() const override;
	void print(std::ostream& os) const override;
private:
	bool isValidEmail(const std::string& email) const;

	std::string email;
};

