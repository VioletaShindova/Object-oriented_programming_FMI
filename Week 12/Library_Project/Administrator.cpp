#include "Administrator.h"

Administrator::Administrator(const std::string& username, const std::string& password, const std::string& email)
    : User(username, password)
{
    setEmail(email);
}

void Administrator::setEmail(const std::string& email)
{
    if (email.empty() || !isValidEmail(email))
        throw std::invalid_argument("Invalid email\n");

    this->email = email;
}

bool Administrator::isAdmin() const
{
    return true;
}

User* Administrator::clone() const
{
    return new Administrator(*this);
}

void Administrator::print(std::ostream& os) const
{
    if(!os.good())
        throw std::runtime_error("Invalid stream\n");

    User::print(os);

    os << email << std::endl;
}

bool Administrator::isValidEmail(const std::string& email) const
{
    size_t atCounter = 0; //@
    size_t dotCounter = 0;
    for (size_t i = 0; i < email.size(); i++)
    {
        if (email[i] == '@') 
            atCounter++;

        if (atCounter != 0 && email[i] == '.' && (i+1) < email.size()) //must update it and check other cases 
            dotCounter++;
    }

    return (atCounter == 1) && (1 <= dotCounter);
}
