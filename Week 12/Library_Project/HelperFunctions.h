#pragma once
#include <string>
#include <vector>
#include <chrono>

std::string readLine(std::istream& istr);

bool isPrefix(const std::string& str, const std::string& prefix);

std::vector<std::string> split(const std::string& input, char separator);

std::string formatTimeYYMMDDhhmmss(std::time_t t);

int parseToInt(const std::string& text);
