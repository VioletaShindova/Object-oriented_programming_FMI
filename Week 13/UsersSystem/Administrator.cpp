#include "Administrator.h"

Administrator::Administrator() : Administrator("pesho@abv.bg", "123") {}

Administrator::Administrator(const char* email, const char* password, int internship, int lvlOfCompetance)
	: User(email, password), internship(0), lvlOfCompetance(1)
{
	setInternship(internship);
	setLevelOfCompetance(lvlOfCompetance);
}
Administrator::Administrator(const User& user, int internship, int lvlOfCompetance)
	: User(user), internship(0), lvlOfCompetance(1)
{
	setInternship(internship);
	setLevelOfCompetance(lvlOfCompetance);
}

void Administrator::setInternship(int internship)
{
	if (internship < 0)
		throw std::invalid_argument("Internship must be a positive number\n");

	this->internship = internship;
}

void Administrator::setLevelOfCompetance(int lvlOfCompetance)
{
	if (!isValidLvlOfCompetance(lvlOfCompetance))
		throw std::invalid_argument("Level of competance must be a value between 1 and 5\n");

	this->lvlOfCompetance = lvlOfCompetance;
}

Administrator& Administrator::operator++()
{
	if (!isValidLvlOfCompetance(lvlOfCompetance + 1))
		throw std::logic_error("Reached full level of competance\n");
	lvlOfCompetance++;
	return *this;
}
Administrator Administrator::operator++(int)
{
	Administrator temp(*this);
	++(*this);
	return temp;
}

Administrator& Administrator::operator--()
{
	if (!isValidLvlOfCompetance(lvlOfCompetance + 1))
		throw std::logic_error("Reached low border of level of competance\n");
	lvlOfCompetance--;
	return *this;
}

Administrator Administrator::operator--(int)
{
	Administrator temp(*this);
	--(*this);
	return temp;
}

std::ostream& operator<<(std::ostream& os, const Administrator& other)
{
	os << static_cast<const User&>(other);
	return os << other.internship << ' ' << other.lvlOfCompetance;
}

std::istream& operator>>(std::istream& is, Administrator& other)
{
	User user;
	is >> user;

	int tempInternship, tempCompetance;
	if (!(is >> tempInternship >> tempCompetance))
	{
		is.clear();
		is.sync();
		throw std::runtime_error("Invalid input\n");
	}

	other = Administrator(user, tempInternship, tempCompetance);

	return is;
}

bool isValidLvlOfCompetance(int lvlOfCompetance)
{
	return (1 <= lvlOfCompetance) && (lvlOfCompetance <= 5);
}

bool operator<(const Administrator& lhs, const Administrator& rhs)
{
	return lhs.getLevelOfCompetance() < rhs.getLevelOfCompetance();
}

bool operator<=(const Administrator& lhs, const Administrator& rhs)
{
	if (lhs.getLevelOfCompetance() == rhs.getLevelOfCompetance())
		return !(rhs.getInternship() < lhs.getInternship());
	return !(rhs < lhs);
}

bool operator>(const Administrator& lhs, const Administrator& rhs)
{
	return rhs < lhs;
}

bool operator>=(const Administrator& lhs, const Administrator& rhs)
{
	if (lhs.getLevelOfCompetance() == rhs.getLevelOfCompetance())
		return !(lhs.getInternship() < rhs.getInternship());
	return !(lhs < rhs);
}
