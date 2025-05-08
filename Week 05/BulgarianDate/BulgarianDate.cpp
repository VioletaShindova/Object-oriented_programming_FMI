#include "BulgarianDate.h"
#include <iostream>

BulgarianDate::BulgarianDate(int day, int month, int year) {
	setYear(year);
	setMonth(month);
	setDay(day);
}

void BulgarianDate::setDay(int day) {
	if (!isValidDay(day))
		throw std::out_of_range("Invalid number for a day!");

	if (isEdgeCase(day))
		day = 14;

	this->day = day;
}

void BulgarianDate::setMonth(int month) {
	if (!isValidMonth(month))
		throw std::out_of_range("Invalid number for a month!");

	if (this->isLeapYear)
		this->max_days[1] = 29;

	this->month = (Month)month;
}

void BulgarianDate::setYear(int year) {
	if (!isValidYear(year))
		throw std::out_of_range("Invalid number for a year!");

	if (isYearLeap(year))
		this->isLeapYear = true;

	this->year = year;
}

const unsigned& BulgarianDate::getDay() const {
	return this->day;
}

DayOfWeek BulgarianDate::getDayOfWeek() const {
	return (DayOfWeek)this->day;
}

const int& BulgarianDate::getMonth() const {
	return (int)this->month;
}

const unsigned& BulgarianDate::getYear() const {
	return this->year;
}

void BulgarianDate::goToNextDay() {
	if (!isValidDay(this->day + 1)) {
		if (!isValidMonth((int)this->month + 1)) {
			if (isValidYear(this->year)) {
				setYear(this->year + 1);
				this->day = 1;
				this->month = Month::JANUARY;

				return;
			}
		}
		this->month = (Month)((int)this->month + 1);
		this->day = 1;
		if (isEdgeCase(this->day + 1)) {
			this->day = 14;
			return;
		}
	}
	this->day++;
}

void BulgarianDate::print() const {
	std::cout << "Day: " << this->day << " Month: " << (int)this->month << " Year: " << this->year << std::endl;
}

bool BulgarianDate::isEdgeCase(int day) const {
	return (this->year == 1916) &&
		((int)this->month == 4) &&
		(1 <= day && day < 14);
}

bool BulgarianDate::isValidDay(int day) const {
	return (1 <= day) && (day <= max_days[(unsigned)this->month - 1]);
}

bool BulgarianDate::isValidMonth(int month) const {
	return ((int)Month::JANUARY <= month) && (month <= (int)Month::DECEMBER);
}

bool BulgarianDate::isValidYear(int year) const {
	return 1 <= year;
}

bool BulgarianDate::isYearLeap(int year) const {
	return (year % 400) == 0;
}

int compareBulgarianDates(const BulgarianDate& lhs, const BulgarianDate& rhs) {
	if (lhs.getYear() < rhs.getYear())
		return -1;
	else if (lhs.getYear() > rhs.getYear())
		return 1;
	else {
		if ((int)lhs.getMonth() < (int)rhs.getMonth())
			return -1;
		else if ((int)lhs.getMonth() > (int)rhs.getMonth())
			return 1;
		else {
			if (lhs.getDay() < rhs.getDay())
				return -1;
			else if (lhs.getDay() > rhs.getDay())
				return 1;
			else
				return 0;
		}
	}
}