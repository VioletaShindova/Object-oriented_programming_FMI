#pragma once

enum class Month {
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class DayOfWeek {
	INVALID = -1, 
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
	DAYS_COUNT
};

class BulgarianDate
{
public:
	BulgarianDate() = default;

	BulgarianDate(int day, int month, int year);

	void setDay(int day);

	void setMonth(int month);

	void setYear(int year);

	const unsigned& getDay() const;

	DayOfWeek getDayOfWeek() const;

	const int& getMonth() const;

	const unsigned& getYear() const;

	void goToNextDay();

	void print() const;

private:
	bool isEdgeCase(int day) const;

	bool isValidDay(int day) const;

	bool isValidMonth(int month) const;

	bool isValidYear(int year) const;

	bool isYearLeap(int year) const;

	unsigned max_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	unsigned day = 1;
	Month month = Month::JANUARY;
	unsigned year = 1;

	bool isLeapYear = false;
};

//can't be static because it is being used in more than 1 cpp files
int compareBulgarianDates(const BulgarianDate& lhs, const BulgarianDate& rhs);
