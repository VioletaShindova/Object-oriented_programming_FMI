#include "HelperFunctions.h"
#include <iostream>

std::string readLine(std::istream& istr) {
	if (!istr.good()) {
		throw std::runtime_error("Stream is not good\n");
	}
	
	std::string result;
	std::getline(istr, result);

	return result;
}

bool isPrefix(const std::string& str, const std::string& prefix)
{
	if (prefix.size() > str.size())
		return false;
	return str.compare(0, prefix.size(), prefix) == 0;
}

std::vector<std::string> split(const std::string& input, char separator)
{
    std::vector<std::string> result;
    std::string current;

    for (char ch : input) {
        if (ch == separator) {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
        }
        else {
            current += ch;
        }
    }

    if (!current.empty()) {
        result.push_back(current);
    }

    return result;
}

std::string formatTimeYYMMDDhhmmss(std::time_t t) {
    std::tm timeinfo;
    localtime_s(&timeinfo, &t); 

    char buffer[20]; 
    std::strftime(buffer, sizeof(buffer), "%y-%m-%d %H:%M:%S", &timeinfo);

    return std::string(buffer);
}

int parseToInt(const std::string& text)
{
    size_t textSize = text.size();
    int number = 0;
    for (size_t i = 0; i < textSize; i++)
    {
        if ('0' <= text[i] && text[i] <= '9') {
            (number += (text[i] - '0'));
            number *= 10;
        }
    }
    return number;
}
