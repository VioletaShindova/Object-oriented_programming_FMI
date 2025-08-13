// ItemsInBar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Bar.hpp"
#include "Drink.hpp"
#include "NonAlcoholic.h"
#include "Alcoholic.hpp"

int main()
{
	Bar b;

	Drink** drinks = new Drink * [3];
	drinks[0] = new NonAlcoholic("Coke", 330);
	drinks[1] = new NonAlcoholic("Fanta", 500);
	drinks[2] = new Alcoholic("Zagorka", 500, 5);

	b.addDrink(drinks[0], 2); //2x Coca cola 330 ml

	b.addDrink(drinks[1]);   //1x Fanta 500 ml
	b.addDrink(drinks[2]);   //Zagorka 500 ml

	b.getDrink(drinks[2]);

	std::cout << b.getMLSold() << std::endl;
	std::cout << b.getAlocholDrinksSold() << std::endl;

	b.getDrink(drinks[0]);
	std::cout << b.getMLSold() << std::endl;
	std::cout << b.getAlocholDrinksSold();
}
