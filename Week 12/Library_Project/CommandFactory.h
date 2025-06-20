#pragma once
#include "Command.h"
#include "LogoutCommand.h"
#include "LoginCommand.h"
#include "AddCommand.h"
#include "PrintCommand.h"
#include "InfoCommand.h"
#include "HelperFunctions.h"
#include "FindCommand.h"
#include "FindUserCommand.h"
#include "AddBookCommand.h"
#include "AddSeriesCommand.h"
#include "AddNewsletterCommand.h"
#include "HelpCommand.h"
#include "ExitCommand.h"

class CommandFactory
{
public:
	static Command* createCommand(const std::string& command, Library& lib);
};

