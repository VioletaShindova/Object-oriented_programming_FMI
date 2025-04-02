// Ex5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Message.h"

using std::cin;
using std::cout;
using std::endl;

/*
Да се направи функция, която "разшифрова" скрито съобщение.

Съобщението представлява двоичен файл с неизвестна дължина. Това, което съхранява е поредица от цели неотрицателни числа.

"Ключът" за съобщението се съхранява в друг двоичен файл и представлява число в интервала [0, 255]. 
Преценете как е най-подходящо да прочетете и съхраните ключа.

Шифърът за получаване на правилното съобщение е към всяко число от прочетения файл, 
съдържащ съобщението да се добави стойността на прочетения ключ

Пояснение: ако файлът със скритото съобщение след прочитане изглежда така: 23 48 3 12 4006

А файлът, съдържащ ключа има стойност 2,

то разшифрованото съобщение трябва да е: 25 50 5 14 4008

Изведете разшифрованото съобщение на конзолата.

Пояснение 2: функцията ви трябва да има следната сигнатура

	void decypherMessage(const char* rawMessageFileName, const char* keyFileName )
*/

int main()
{
	int size;
	cout << "Input size: ";

	cin >> size;
	int key;
	cout << "Input key: ";
	cin >> key;

	unsigned* messages = new unsigned[size];
	for (size_t i = 0; i < size; i++)
	{
		cin >> messages[i];
	}

	Message msg2;
	try {
		msg2 = Message(messages, size, key);
	}
	catch (const std::exception& e) {
		cout << e.what();
	}

	if (!msg2.writeToBinaryFile("ex5_MessagesInBinaryFile.dat"))
		return 0;

	Message msg3;
	try {
		msg3 = Message(size);
	}
	catch (const std::exception& e) {
		cout << e.what();
	}

	if (!msg3.readFromBinaryFile("ex5_MessagesInBinaryFile.dat"))
		return 0;

	msg3.print();
	cout << endl;

	if (!msg2.writeToBinaryFileUsingKey("ex5_MessagesInBinaryFile.dat"))
		return 0;

	Message msg4;
	try {
		msg4 = Message(size);
	}
	catch (const std::exception& e) {
		cout << e.what();
	}

	if (!msg4.readFromBinaryFile("ex5_MessagesInBinaryFile.dat"))
		return 0;

	msg4.print();
}