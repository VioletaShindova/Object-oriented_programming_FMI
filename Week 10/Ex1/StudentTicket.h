#pragma once
#include "Ticket.h"

class StudentTicket : public Ticket
{
public:
	StudentTicket();

	StudentTicket(const MyString& name, double originalPrice);
	
private:

};

