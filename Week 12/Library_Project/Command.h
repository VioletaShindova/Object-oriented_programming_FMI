#pragma once
//#include "Library.h"
#include "User.h"
#include "Item.h"

class Library;
class Command
{
public:
	Command() = default;
	Command(Library& lib);

	virtual void execute() const = 0;
	virtual bool isExcutable() const = 0;
	virtual ~Command() noexcept = default;
protected:
	Library& lib;
};

