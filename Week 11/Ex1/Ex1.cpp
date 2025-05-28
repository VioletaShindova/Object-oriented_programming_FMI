// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vehicle.h"
#include "Bicycle.h"
#include "Car.h"

using std::cin;
using std::cout;
using std::endl;

/*
Напишете клас Vehicle, представляващ превозно средство. Обектите от този клас съдържат информация за:

цвят
марка
година на производство
брой места/брой пътници, които може да превози
максимална скорост, която превозното средство може да развие

Напишете клас Bicycle, наследяващ Vehicle. Освен това, той има и полета с информация за:

брой скорости
дали има светлини
дали има звънче
Да се реализира клас Car, наследяващ Vehicle. Този клас съдържа още:

модел
брой врати
мощност на двигателя в конски сили.

За Vehicle, Bicycle и Car, реализирайте конструктор по подразбиране, 
копиращ конструктор, оператор = и деструктор за класа.
По желание да се реализират и други конструктори, 
като е желателно да се добавят и гетъри и сетъри за собствените полета на класа.
*/

int main()
{
    Vehicle** ptr = new Vehicle * [3];

    ptr[0] = new Vehicle();
    ptr[1] = new Car();
    ptr[2] = new Bicycle();

    Vehicle** ptr1 = new Vehicle * [3];

    ptr1[0] = new Vehicle(Vehicle::Color::BLACK, "abc", 2000, GlobalConstants::MIN_PASSENGERS_CAPACITY, GlobalConstants::MIN_SPEED_CAPACITY);
    ptr1[1] = new Car(*ptr1[0], "car1", GlobalConstants::MIN_DOORS_COUNT, GlobalConstants::MIN_CAR_HORSEPOWER);
    ptr1[2] = new Bicycle(Vehicle::Color::BLACK, "abc", 2000, GlobalConstants::MIN_PASSENGERS_CAPACITY, GlobalConstants::MIN_SPEED_CAPACITY, GlobalConstants::MIN_SIZE_GEARS, true, true);




    for (size_t i = 0; i < 3; i++)
        delete ptr[i];

    delete[] ptr;

    for (size_t i = 0; i < 3; i++)
        delete ptr1[i];

    delete[] ptr1;
}

