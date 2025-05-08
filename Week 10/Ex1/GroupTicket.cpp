#include "GroupTicket.h"

GroupTicket::GroupTicket() : GroupTicket("", 0) {}

GroupTicket::GroupTicket(const MyString& name, double originalPrice) : Ticket(name, originalPrice - ((double)20 / 100) * originalPrice) {}