#include "System.h"
#include "User.h"
#include "SuperUser.h"
#include "Administrator.h"
#pragma warning(disable : 4996)

System::System() : System("unknown") {}

System::System(const char* name)
	: name(nullptr), users(nullptr), size(0), capacity(1)
{
	setName(name);

	try {
		setUsers(capacity);
	}
	catch (std::bad_alloc& ba)
	{
		delete[] name;
		std::cerr << "Bad allocation\n";
		throw ba;
	}
	catch(std::invalid_argument& inv_arg)
	{
		delete[] name;
		std::cerr << inv_arg.what();
		throw inv_arg;
	}
}

System::System(const System& other)
	: size(other.size), capacity(other.capacity)
{
	copyDynamic(other);
}

System::~System() noexcept
{
	freeDynamic();
}

void System::setName(const char* name)
{
	if (!name || strlen(name))
		throw std::invalid_argument("Invalid name\n");

	char* temp = new (std::nothrow) char[strlen(name) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, name);
	delete[] this->name;
	this->name = nullptr;
}

void System::setUsers(int capacity)
{
	if (capacity < 0 || capacity < size)
		throw std::invalid_argument("Invalid capacity\n");

	User** temp = new (std::nothrow) User * [capacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = new (std::nothrow) User(*users[i]);
		if (!temp[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete temp[j];
			}
			delete[] temp;
			throw std::bad_alloc();
		}
	}

	for (size_t i = 0; i < size; i++)
		delete users[i];
	delete[] users;
	users = temp;
	this->capacity = capacity;
}

void System::setUsers(User** users, int size)
{
	if (!users || size <= 0 || !isFoundSingleSuperUser(users, size))
		throw std::invalid_argument("Invalid arguments\n");

	User** temp = new (std::nothrow) User * [size + 1] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = new (std::nothrow) User(*users[i]);

		if (!temp[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete temp[j];
			}
			delete[] temp;
			throw std::bad_alloc();
		}
	}

	for (size_t i = 0; i < size; i++)
		delete this->users[i];
	delete[] this->users;
	this->users = temp;
	this->size = size;
	capacity = size + 1;
}

System& System::operator+=(const User* rhs)
{
	if (!rhs)
		throw std::invalid_argument("Invalid user\n");

	if (existsUser(rhs) || (dynamic_cast<const SuperUser*>(rhs) && isFoundSingleSuperUser(users, size)))
		throw std::logic_error("User already exists or can't have more than one super users\n");

	User* temp = new (std::nothrow) User(*rhs);

	if (!temp)
		throw std::bad_alloc();

	if (size + 1 >= capacity)
		resize();

	users[size++] = temp;

	return *this;
}

System& System::operator-=(const User* rhs)
{
	if (!rhs)
		throw std::invalid_argument("Invalid user\n");

	if (!existsUser(rhs) || size == 0)
		throw std::logic_error("User doesn't exist\n");

	if (dynamic_cast<const SuperUser*>(rhs))
		throw std::logic_error("You can remove only users or administrators\n");

	if (dynamic_cast<const Administrator*>(rhs) && getCountOfAdmins() == 1)
		throw std::logic_error("Can't remove the last administrator\n");

	for (size_t i = 0; i < size; i++)
	{
		if (*users[i] == *rhs)
		{
			std::swap(users[i], users[size - 1]);
			delete users[size - 1];
			users[size - 1] = nullptr;
			size--;
			break;
		}
	}
	return *this;
}

bool System::operator()(const Administrator* toAddAdmin)
{
	if (!toAddAdmin)
		throw std::invalid_argument("Invalid admin\n");

	if (existsUser(toAddAdmin))
		throw std::logic_error("Admin already exists\n");

	if (dynamic_cast<const SuperUser*>(toAddAdmin))
	{
		if (isFoundSingleSuperUser(users, size))
			throw std::logic_error("There is already one super user\n");

		SuperUser* temp = new (std::nothrow) SuperUser(*toAddAdmin);

		if (!temp)
			throw std::bad_alloc();

		if (size + 1 >= capacity)
			resize();

		users[size++] = temp;
		return true;
	}
	return false;
}

Administrator* System::operator^(int lvlOfCompetance)
{
	if (!isValidLvlOfCompetance(lvlOfCompetance))
		throw std::invalid_argument("Invalid level of competance\n");

	for (size_t i = 0; i < size; i++)
	{
		Administrator* admin;
		if ((admin = dynamic_cast<Administrator*>(users[i])) && admin->getLevelOfCompetance() <= lvlOfCompetance)
			return admin;
	}
	return nullptr;
}

size_t System::getCountOfAdmins() const
{
	size_t result = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (dynamic_cast<const Administrator*>(users[i]))
			result++;
	}
	return result;
}

bool System::existsUser(const User* toFind) const
{
	if (!toFind)
		throw std::invalid_argument("Invalid user\n");

	for (size_t i = 0; i < size; i++)
	{
		if (*users[i] == *toFind)
			return true;
	}
	return false;
}

bool System::isFoundSingleSuperUser(User** users, int size) const
{
	if (!users || size <= 0)
		throw std::invalid_argument("Empty users\n");

	unsigned superUserCounter = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (dynamic_cast<const SuperUser*>(users[i]))
			superUserCounter++;
	}
	return superUserCounter == 1;
}

void System::freeDynamic()
{
	delete[] name;

	for (size_t i = 0; i < size; i++)
		delete users[i];
	delete[] users;

	name = nullptr;
	users = nullptr;
}

void System::copyDynamic(const System& other)
{
	char* tempName = new (std::nothrow) char[strlen(other.name) + 1];

	if (!tempName)
		throw std::bad_alloc();

	strcpy(tempName, other.name);

	User** tempUsers = new (std::nothrow) User * [other.capacity] {nullptr};

	if (!tempUsers)
	{
		delete[] tempName;
		throw std::bad_alloc();
	}

	for (size_t i = 0; i < other.size; i++)
	{
		tempUsers[i] = new (std::nothrow) User(*other.users[i]);

		if (!tempUsers[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete tempUsers[j];
			}
			delete[] tempUsers;
			delete[] tempName;
			throw std::bad_alloc();
		}
	}

	name = tempName;
	users = tempUsers;
}

void System::resize()
{
	size_t tempCapacity = capacity * 2 + 1;
	User** temp = new (std::nothrow) User * [tempCapacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = new (std::nothrow) User(*users[i]);

		if (!temp[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete temp[j];
			}
			delete[] temp;
			throw std::bad_alloc();
		}
	}

	for (size_t i = 0; i < size; i++)
		delete users[i];
	delete[] users;
	users = temp;
	capacity = tempCapacity;
}

std::ostream& operator<<(std::ostream& os, const System& other)
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	os << other.name << ' ' << other.size << ' ' << other.capacity;
	for (size_t i = 0; i < other.size; i++)
	{
		os << ' ' << other.users[i];
	}
	return os << '\n';
}

std::istream& operator>>(std::istream& is, System& other)
{
	if (!is.good())
		throw std::runtime_error("Stream is not good\n");

	char buffer[128];
	is.getline(buffer, 128, ' ');

	other.setName(buffer);

	int size, capacity;
	if (!(is >> size >> capacity))
	{
		is.clear();
		is.sync();
		throw std::runtime_error("Invalid input\n");
	}

	User** tempUsers = new (std::nothrow) User * [capacity] {nullptr};

	for (size_t i = 0; i < size; i++)
		is >> *tempUsers[i];

	other.setUsers(tempUsers, size);
}

System operator+(const System& lhs, const User* rhs)
{
	System temp(lhs);
	temp += rhs;	
	return temp;
}

System operator-(const System& lhs, const User* rhs)
{
	System temp(lhs);
	temp -= rhs;
	return temp;
}
