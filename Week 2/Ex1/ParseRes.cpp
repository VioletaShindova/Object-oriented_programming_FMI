#include "ParseRes.h"

ParseResult parse(const char* text)
{
	if (!text)
	{
		return { 0, false };
	}

	ParseResult res;

	unsigned counter = 10;
	 
	while (*text)
	{
		if ((*text) >= '0' && (*text) <= '9')
		{
			res.number *= counter;
			res.number += ((*text) - '0');
			
		}
		else
		{
			return { 0, false };
		}
		text++;
	}

	res.status = true;

	return res;
}