#include <iostream>
#include "Library.h"
#include "User.h"
#include "Book.h"

using std::cin;
using std::cout;
using std::endl;

/*
Да се разработи система за управление на книги в библиотека.

Създайте клас Book, който описва книга в библиотеката. Всяка книга има:

Уникален идентификатор (ID), който се генерира автоматично
Заглавие (низ с произволна дължина)
Автор (низ с произволна дължина)
Статус (дали книгата е налична за заемане)

Създайте клас User- описва потребител, който може да заема книги. Всеки потребител има:

потребителско име (до 8 символа)
телефонен номер за връзка (до 10 символа)

Създайте клас Library - библиотека, която съдържа списък от книги (до 50).

Реализирайте следните функционалности:

Добавяне на нова книга, ако капацитетът го позволява
Заемане на книга по дадено ID и име на потребителя – отбелязва книгата като "заета" и кой потребител я е заел
Връщане на книга по дадено ID – отбелязва книгата като "налична"
Извеждане на информация – принтира ID, заглавие, автор и статус
При опит за заемане на вече заета книга или връщане на вече налична книга, се хвърля изключение. 
Всички възникнали изключения се обработват, за да не достигнат до крайния потребител.
*/

int main()
{
    User user1;
	try {
		user1 = User("Ivan", "0893580453");
	} 
	catch (const std::invalid_argument& inv_arg) {
		cout << inv_arg.what();
	}

	User user2("Moni", "1234567890");
	User user3;

	user3.setName("Cani");
	user3.setNumber("0987654321");

	user3.print();

	Library lib1;

	cout << lib1.addBook({ "Queen", "Freddie Mercury" }) << endl;
	cout << lib1.addBook({ "Twilight", "Stephanie Meyer" }) << endl;
	cout << lib1.addBook({ "Tess of the d'Urbervilles", "Thomas Hardy" }) << endl;
	cout << lib1.addBook({ "Passengers", "Avicci" }) << endl;
	cout << lib1.makeBookTakenBy(2, user1) << endl;
	cout << lib1.makeBookFree(2) << endl;

	try {
		cout << lib1.makeBookFree(2) << endl;
	}
	catch (const std::invalid_argument& inv_arg) {
		cout << inv_arg.what();
	}

	cout << endl;
	lib1.print();
}

