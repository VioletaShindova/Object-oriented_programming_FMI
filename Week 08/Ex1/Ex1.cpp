#include <iostream>
#include "MyString.h"

using std::cin;
using std::cout;
using std::endl;

/*
Създайте клас MyString, който съдържа съдържа следните член-функции:

at(index) - Връща символ от низа на даден индекс
front() - Връща първия елемент на низа, ако има такъв
back() - Връща последния елемент на низа, ако има такъв
c_str() - Връща самия низ, който се съдържа в MyString
size() - Връща дължината на низа
capacity() - Връща количеството заделена памет за низа
empty() - Връща дали стринга е празен
append(<подходящ/и параметър/и>) - Долепя нов символ, низ или друг стринг
clear() - Изчиства съдържанието на обекта, без да променя капацитета
equals(<подходящ/и параметър/и) - Проверява дали два низа са равни
find(ch) - Намира индекса на първото срещане на даден символ. Ако такъв символ не е намерен, трябва да се върне -1.
find(str) - Намира индекса на първото срещане на подниза str в низа. Ако такъв подниз не е намерен, трябва да се върне -1.
*/

int main()
{
	MyString str1;
	try {
		str1 = MyString("ABC");
	}
	catch (const std::invalid_argument& inv_arg) {
		cout << inv_arg.what();
	}

	cout << str1.at(2) << endl;
	cout << str1.front() << endl;
	cout << str1.back() << endl;
	cout << str1.append("D") << endl;
	cout << str1.find('C') << endl;
	cout << str1.find('E') << endl;
	cout << str1.find("BCD") << endl;

	MyString str2("ABCDE");

	cout << "Are str1 and str2 quals: " << equals(str1, str2) << endl;

	MyString str3("Hello");
	str3.print();
}
