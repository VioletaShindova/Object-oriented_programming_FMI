// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Създайте структура ParseResult, която представлява резултат от превръщане на низ в число (parse-ване) 
и съдържа число и статус код (който може да бъде OK или Error). Също така, реализирайте функция parse, 
която приема символен низ, превръща го в число и връща ParseResult.
Пример:
Вход:

"123"
Изход:

{number: 123, statusCode: OK}
Вход:

"12d3"
Изход:

{number: _, statusCode: Error}
*/

#include <iostream>
#include "ParseRes.h"

int main()
{
	char text[] = "12378472836478223";
	ParseResult	res = parse(text);

	if (res.status)
	{
		std::cout << "number: " << res.number << " statusCode: OK";
	}
	else
	{
		std::cout << "number: _, " << "statusCode: ERROR";
	}
}

