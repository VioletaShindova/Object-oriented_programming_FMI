// Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Computer.h"
#include "PC.h"
#include "Laptop.h"
#include "GamingConsole.h"

/*
Да се реализира йерархия от компютри.

Създайте абстрактен клас Computer, който съдържа:

Мощност на процесора (число тип double)
Модел на видео картата (масив от символи)
Мощност на захранването (цяло число)
Количество RAM памет (цяло число)
Методи за промяна на компонентите на компютъра
Функция, която изписва на стандартния изход какъв тип е компютъра (PC, лаптоп или геймърска конзола)
Функция, която връща с какви периферни устройства може да се свързва компютъра.
Нека перферните устройства са масиви от символи.

Създайте класове PC, Laptop и GamingConsole

PC може да се свързва с мишка, клавиатура, микрофон и слушалки.
Laptop - с mouse pad, клавиатура и монитор.
GamingConsole - с джойстик и монитор.
*/

int main()
{
	Computer** ptr = new Computer * [3];

	ptr[0] = new PC();
	ptr[1] = new Laptop();
	ptr[2] = new GamingConsole();

	ptr[0]->typeOfComputer();
	ptr[1]->typeOfComputer();
	ptr[2]->typeOfComputer();

	ptr[0]->peripheralsToConnectTo();
	ptr[1]->peripheralsToConnectTo();
	ptr[2]->peripheralsToConnectTo();

	delete ptr[2];
	delete ptr[1];
	delete ptr[0];

	delete[] ptr;
}

