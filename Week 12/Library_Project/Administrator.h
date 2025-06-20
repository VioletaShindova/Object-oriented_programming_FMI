#pragma once
#include "User.h"
#include "HelperFunctions.h"
#include <string>
#include <fstream>

class Administrator : public User
{
public:
	Administrator() = delete;
	Administrator(const std::string& username, const std::string& password, const std::string& email);

	void setEmail(const std::string& email);

	bool isAdmin() const override;
	User* clone() const override;
	void print(std::ostream& os) const override;

	void saveAllToFile(std::ofstream& ofs) const override;

	std::string getType() const override;

	static Administrator* loadFromFile(const std::string& line);
private:
	bool isValidEmail(const std::string& email) const;

	std::string email;
};

