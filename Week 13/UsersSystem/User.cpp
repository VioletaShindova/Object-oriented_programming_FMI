#include "User.h"
#pragma warning (disable : 4996)

User::User() : User("pesho@abv.bg", "123") {}

User::User(const char* email, const char* password)
    : email(nullptr), password(nullptr)
{
    setEmail(email);

    try {
        setPassword(password);
    }
    catch (std::bad_alloc& ba)
    {
        delete[] email;
        std::cerr << "Bad allocation\n";
        throw ba;
    }
    catch (std::invalid_argument& inv_arg)
    {
        delete[] email;
        std::cerr << inv_arg.what();
        throw inv_arg;
    }
}

User::User(const User& other)
{
    copyDynamic(other);
}

User& User::operator=(const User& other)
{
    if (this != &other)
    {
        freeDynamic();
        copyDynamic(other);
    }
    return *this;
}

User::~User() noexcept
{
    freeDynamic();
}

void User::setEmail(const char* email)
{
    if (!email || strlen(email) == 0 || !isValidEmail(email))
        throw std::invalid_argument("Invalid email\n");


    char* temp = new (std::nothrow) char[strlen(email) + 1];
    
    if (!temp)
        throw std::bad_alloc();

    strcpy(temp, email);
    delete[] this->email;
    this->email = temp;
}

void User::setPassword(const char* password)
{
    if (!password || strlen(password) == 0)
        throw std::invalid_argument("Invalid password\n");

    char* temp = new (std::nothrow) char[strlen(password) + 1];

    if (!temp)
        throw std::bad_alloc();

    strcpy(temp, password);
    delete[] this->password;
    this->password = temp;
}

std::ostream& operator<<(std::ostream& os, const User& other)
{
    if (!os.good())
        throw std::runtime_error("Stream is not good\n");

    return os << other.getEmail() << ' ' << other.getPassword() << ' ';
}

std::istream& operator>>(std::istream& is, User& other)
{
    if (!is.good())
        throw std::runtime_error("Stream is not good\n");

    char tempEmail[128];
    is.getline(tempEmail, 128, ' ');

    char tempPassword[128];
    is.getline(tempPassword, 128, ' ');

    other = User(tempEmail, tempPassword);

    return is;
}

bool User::isValidEmail(const char* email) const
{
    if (!email || strlen(email) == 0)
        throw std::invalid_argument("Invalid email\n");

    unsigned counter = 0;
    while (*email)
    {
        if (*email == '@')
            counter++;
        email++;
    }

    return counter == 1;
}

void User::freeDynamic()
{
    delete[] email;
    delete[] password;;

    email = nullptr;
    password = nullptr;
}

void User::copyDynamic(const User& other)
{
    char* tempEmail = new (std::nothrow) char[strlen(other.email) + 1];

    if (!tempEmail)
        throw std::bad_alloc();

    strcpy(tempEmail, other.email);

    char* tempPassword = new (std::nothrow) char[strlen(other.password) + 1];

    if (!tempEmail)
    {
        delete[] tempEmail;
        throw std::bad_alloc();
    }

    strcpy(tempPassword, other.password);

    delete[] email;
    email = tempEmail;

    delete[] password;
    password = tempPassword;
}

bool operator==(const User& lhs, const User& rhs)
{
    return strcmp(lhs.getEmail(), rhs.getEmail()) == 0;
}

bool operator!=(const User& lhs, const User& rhs)
{
    return !(lhs == rhs);
}
