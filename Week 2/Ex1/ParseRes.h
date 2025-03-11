#pragma once

struct ParseResult {
	unsigned number = 0;
	bool status = false;
};

ParseResult parse(const char* text);
