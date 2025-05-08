#pragma once
#include "Ticket.h"

class GroupTicket : public Ticket
{
public:
	GroupTicket();

	GroupTicket(const MyString& name, double originalPrice);
private:

};

