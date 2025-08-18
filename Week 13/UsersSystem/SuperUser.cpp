#include "SuperUser.h"
#pragma warning (disable : 4996)

SuperUser::SuperUser() : SuperUser("pesho@abv.bg", "123") {}

SuperUser::SuperUser(const char* email, const char* password, int internship, int lvlOfCompetance, int capacity)
	: Administrator(email, password, internship, lvlOfCompetance), usernames(nullptr), size(0), capacity(1) {}

SuperUser::SuperUser(const User& user, int internship, int lvlOfCompetance, int capacity) 
	: Administrator(user, internship, lvlOfCompetance), usernames(nullptr), size(0), capacity(1) {}

SuperUser::SuperUser(const SuperUser& other) : Administrator(other), size(other.size), capacity(other.capacity)
{
	copyDynamic(other);
}

SuperUser& SuperUser::operator=(const SuperUser& other)
{
	if (this != &other)
	{
		Administrator::operator=(other);
		size = other.size;
		capacity = other.capacity;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}
SuperUser::~SuperUser() noexcept
{
	freeDynamic();
}

void SuperUser::operator()()
{
	using std::cin;
	using std::cout;

	cout << "Input username/email: ";
	char bufferEmail[128];
	cin >> bufferEmail;

	cout << "Input password: ";
	char bufferPassword[128];
	cin >> bufferPassword;

	User user(bufferEmail, bufferPassword);

	char* tempUserName = new (std::nothrow) char[strlen(bufferEmail) + 1];

	if (!tempUserName)
		throw std::bad_alloc();

	strcpy(tempUserName, bufferEmail);	

	if (size + 1 > capacity)
		resize();

	usernames[size++] = tempUserName;
}

void SuperUser::setUserNames(char** usernames, int size)
{
	if (!usernames || size < 0)
		throw std::invalid_argument("Invalid usernames\n");

	char** temp = new (std::nothrow) char* [size] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = new (std::nothrow) char[strlen(usernames[i]) + 1];

		if (!temp[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete[] temp[j];
			}
			delete[] temp;
			throw std::bad_alloc();
		}
		strcpy(temp[i], usernames[i]);
	}

	for (size_t i = 0; i < this->size; i++)
		delete[] this->usernames[i];
	delete[] this->usernames;
	this->usernames = temp;
	this->size = size;
}

void SuperUser::freeDynamic()
{
	for (size_t i = 0; i < size; i++)
		delete[] usernames[i];
	delete[] usernames;
	usernames = nullptr;
}

void SuperUser::copyDynamic(const SuperUser& other)
{
	char** temp = new (std::nothrow) char* [other.capacity] {nullptr};

	if (!temp)	
		throw std::bad_alloc();

	for (size_t i = 0; i < other.size; i++)
	{
		if (other.usernames[i])
		{
			temp[i] = new (std::nothrow) char[strlen(other.usernames[i]) + 1];

			if (!temp[i])
			{
				for (size_t j = 0; j < i; j++)
				{
					delete[] temp[j];
				}
				delete[] temp;
				throw std::bad_alloc();
			}

			strcpy(temp[i], other.usernames[i]);
		}
		else
			temp[i] = nullptr;
	}
	usernames = temp;
}

void SuperUser::resize()
{
	size_t tempCapacity = capacity * 2 + 1;

	char** temp = new (std::nothrow) char* [tempCapacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = new (std::nothrow) char[strlen(usernames[i]) + 1];

		if (!temp[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete[] temp[j];
			}
			delete[] temp;
			throw std::bad_alloc();
		}

		strcpy(temp[i], usernames[i]);
	}

	for (size_t i = 0; i < size; i++)
		temp[i] = usernames[i];
	delete[] usernames;
	usernames = temp;
	capacity = tempCapacity;
}

std::ostream& operator<<(std::ostream& os, const SuperUser& other)
{
	os << static_cast<const Administrator&>(other);

	os << other.size << ' ' << other.capacity;
	
	for (size_t i = 0; i < other.size; i++)
	{
		os << ' ' << other.usernames[i];
	}

	return os << '\n';
}

std::istream& operator>>(std::istream& is, SuperUser& other)
{
	Administrator admin;
	is >> admin;

	size_t size, capacity;
	if (!(is >> size >> capacity))
	{
		is.clear();
		is.sync();
		throw std::runtime_error("Invalid input\n");
	}

	char** temp = new (std::nothrow) char* [capacity] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		char buffer[128];
		is.getline(buffer, 128, ' ');

		temp[i] = new (std::nothrow) char[strlen(buffer) + 1];
		if (!temp[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete[] temp[j];
			}
			delete[] temp;
			throw std::bad_alloc();
		}
		strcpy(temp[i], buffer);
	}

	other = admin;
	other.setUserNames(temp, size);
	return is;
}
