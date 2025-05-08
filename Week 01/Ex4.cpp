// Ex4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/*
4. Създайте приложение, което поддържа променлива, която показва кои напитки харесва потребителят.
Възможните напитки са 8 на брой: уиски, водка, кола, фанта, вода, вино, ром, сок.
Също така да се имплементират следните функционалности:

При подадена променлива и напитка да се отговори на въпроса дали потребителят харесва даденото питие.
При подадена променлива и напитка да се промени предпочитанието на потребителя, така че да започне да харесва даденото питие.
При подадена променлива и напитка да се промени предпочитанието на потребителя, така че да спре да харесва даденото питие.
Да се отпечатат всички напитки, които потребителят харесва.
Подсказка: Използвайте битова маска за оптимално съхранение на предпочитанията към напитките.
*/

enum class Drink : uint16_t {
    whiskey = 1, 
    vodka = 1 << 1,  
    cola = 1 << 2,   
    fanta = 1 << 3,  
    water = 1 << 4,
    wine = 1 << 5,
    rum = 1 << 6,
    juice = 1 << 7
};

void addFavoriteDrinks(uint8_t oldDrink, int& preferedDrink)
{
     preferedDrink |= oldDrink;
}

void removeDrink(uint8_t oldDrink, int& preferedDrink)
{
    preferedDrink = (~preferedDrink & oldDrink);
}

bool isDrinkLiked(uint8_t drinks, uint16_t preferedDrink)
{
    return drinks & preferedDrink;
}

void printAllDrinksLikedByUser(uint8_t preferedDrink)
{
    Drink position = Drink::whiskey;
    int mask = (int)position;

    while (mask != 256)
    {
        if (isDrinkLiked(preferedDrink, mask))
        {
            switch (position)
            {
            case Drink::whiskey: std::cout << "whiskey" << std::endl; break;
            case Drink::vodka: std::cout << "vodka" << std::endl; break;
            case Drink::cola: std::cout << "cola" << std::endl; break;
            case Drink::fanta: std::cout << "fanta" << std::endl; break;
            case Drink::water: std::cout << "water" << std::endl; break;
            case Drink::wine: std::cout << "wine" << std::endl; break;
            case Drink::rum: std::cout << "rum" << std::endl; break;
            case Drink::juice: std::cout << "juice" << std::endl; break;

            default:
                break;
            }
        }

        mask <<= 1;
        position = (Drink)mask;
    }
}

void inputPreferedDrink(int& prefferedDrink)
{
    std::cout << "List of drinks - whiskey, vodka, cola, fanta, water, wine, rum, juice: ";

    do
    {
        std::cout << "Choose a drink from the list that is a power of 2 between 1 and 126: ";
        std::cin >> prefferedDrink;
    } while (prefferedDrink < 1 || prefferedDrink > 128);
}

int main()
{
    int prefferedDrink = 0;
    inputPreferedDrink(prefferedDrink);

    uint8_t oldDrink = 0;
    addFavoriteDrinks(oldDrink, prefferedDrink);

    oldDrink = prefferedDrink;
    inputPreferedDrink(prefferedDrink);
    addFavoriteDrinks(oldDrink, prefferedDrink);

    oldDrink = prefferedDrink;
    inputPreferedDrink(prefferedDrink);
    addFavoriteDrinks(oldDrink, prefferedDrink);

    oldDrink = prefferedDrink;
    inputPreferedDrink(prefferedDrink);
    removeDrink(oldDrink, prefferedDrink);

    oldDrink = prefferedDrink;
    printAllDrinksLikedByUser(oldDrink);
}

