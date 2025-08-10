// PhoneAndSmartphone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Shop.hpp"
#include "Phone.hpp"
#include "SmartPhone.hpp"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    Shop shop(3000);
    Phone p1("16", "iphone", 2000);
    Phone p2("18", "iphone", 50);
    shop.addPhone(&p1);
    shop.addPhone(&p2);
    shop.removePhone("16", "iphone");
}
