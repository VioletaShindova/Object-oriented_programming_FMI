#pragma once
#include <string>
#include <vector>
#include <chrono>

std::string readLine(std::istream& istr);

bool isPrefix(const std::string& str, const std::string& prefix);

std::vector<std::string> split(const std::string& input, char separator);

std::string formatTimeYYMMDDhhmmss(std::time_t t);

std::chrono::year_month_day parseDate(const std::string& dateStr);

int parseToInt(const std::string& text);

bool isCorrectISBN(const char* ISBN);

bool isCorrectISSN(const char* ISSN);

//template <typename T>
//std::vector<T*> getOnlyOneType(const std::vector<T*>& container, const std::string& type) {
//	std::vector<T*> result;
//	for (T* obj : container) {
//		if (obj && obj->getType() == type)
//			result.push_back(obj);
//	}
//	return result;
//}
