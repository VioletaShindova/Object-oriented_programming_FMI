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

std::chrono::year_month_day parseDate(const std::string& dateStr)
{
    std::vector<std::string> parts = split(dateStr, '-');

    if (parts.size() != 3)
        throw std::runtime_error("Invalid date format. Expected YYYY-MM-DD");

    int year = parseToInt(parts[0]);
    int month = parseToInt(parts[1]);
    int day = parseToInt(parts[2]);

    return std::chrono::year_month_day{
        std::chrono::year{year},
        std::chrono::month{static_cast<unsigned>(month)},
        std::chrono::day{static_cast<unsigned>(day)}
    };
}

int parseToInt(const std::string& text)
{
    int number = 0;
    for (char ch : text)
    {
        if ('0' <= ch && ch <= '9') {
            number = number * 10 + (ch - '0');
        }
    }
    return number;
}

bool isCorrectISBN(const char* ISBN)
{
    if (!ISBN)
        return false;

    size_t dashCounter = 0;
    size_t digitCounter = 0;

    const char* ptr = ISBN;
    while (*ptr)
    {
        if (*ptr == '-')
            dashCounter++;
        else if (isdigit(*ptr))
            digitCounter++;
        else
            return false; // invalid character

        ptr++;
    }

    return dashCounter == 4 && digitCounter == 13;
}

bool isCorrectISSN(const char* ISSN)
{
    for (int i = 0; i < 9; ++i) {
        if (i == 4) {
            if (ISSN[i] != '-') return false;
        }
        else {
            if (!isdigit(ISSN[i])) return false;
        }
    }
    return true;
}
