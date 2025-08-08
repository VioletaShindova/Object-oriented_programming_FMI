#pragma once

#ifndef __IOHELPERS_HEADER_INCLUDED

#define __IOHELPERS_HEADER_INCLUDED

#include <iostream>

static void skipSpaces(std::istream& is, char symbol) 
{
	if (!is.good())
		throw std::runtime_error("Stream is not good\n");

	is.get();

	char ch = ' ';
	while (is.get(ch))
	{
		if (ch != symbol)
		{
			is.unget();
			break;
		}
	}
}

#endif