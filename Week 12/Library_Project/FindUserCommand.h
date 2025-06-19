#pragma once
#include "Command.h"
#include "Library.h"

class FindUserCommand : public Command
{
public:
	FindUserCommand(Library& lib, const std::string& option, const std::string& value);

	void execute() const override;
	bool isExcutable() const override;
private:
	void findByName() const;
	void findByItemID() const;
	void findByState() const;

	void findOverdueUsers() const;
	void findActiveReaders() const;
	void findInactiveUsers() const;

	std::string option, value;
};

