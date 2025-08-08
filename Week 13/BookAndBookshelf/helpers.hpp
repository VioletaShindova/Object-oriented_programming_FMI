#pragma once

#ifndef __HELPERS_HEADER_INCLUDED_
#define __HELPERS_HEADER_INCLUDED_

static unsigned getDigitsCountOfNumber(int number) {
	unsigned counter = 0;
	while (number / 10 != 0)
	{
		counter++;
		number /= 10;
	}
	return counter;
}

#endif // !__HELPERS_HEADER_INCLUDED_
