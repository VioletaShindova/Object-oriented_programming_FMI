#include "StudentTicket.h"

StudentTicket::StudentTicket() : StudentTicket("", 0) {}

StudentTicket::StudentTicket(const MyString& name, double originalPrice) : Ticket(name, originalPrice / 2) {}