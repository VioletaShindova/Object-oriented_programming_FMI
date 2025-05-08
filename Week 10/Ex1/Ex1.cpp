// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MyString.h"
#include "Ticket.h"
#include "StudentTicket.h"
#include "GroupTicket.h"

using std::cin;
using std::cout;
using std::endl;

/*
Реализирайте клас Ticket, който описва билет за театрална постановка.
Всеки билет има име на постановката от тип MyString (който написахте в практикум 8) и цена от тип double. 
Направете подходящи конструктори.

Реализирайте клас Student Ticket, който е 2 пъти по-евтин. В конструктора си приема име и оригинална цена за постановката. 
Реализирайте клас Group Ticket, който е с 20% по-евтин от нормалния. Направете подходящи функции за принтиране на информацията за билетите.
*/

int main()
{
    StudentTicket st1{"ivan", 24};
    GroupTicket gt1{"pesho", 12};

    st1.print();
    gt1.print();
}
