#pragma once

#ifndef __IOHELPERS_HEADER_INCLUDED
#define __IOHELPERS_HEADER_INCLUDED

void skipSpaces(std::istream& is, char skipSymbol) 
{
	if (!is.good())
		return;

	char ch = ' ';
	while (is.get(ch))
	{
		if (ch != skipSymbol) {
			is.unget(); //returns the non-space symbol back in the stream
			return;
		}	
	}
}

#endif