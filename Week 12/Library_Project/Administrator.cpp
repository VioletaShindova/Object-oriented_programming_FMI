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

void Administrator::saveAllToFile(std::ofstream& ofs) const
{
    if (!ofs.is_open() || !ofs.good())
        throw std::runtime_error("Something wrong with stream - it is either bad or it can't be opened\n");

    ofs << getUsername() << "," << getPassword() << "," << getYMD() << "," << getLastLogInDate();

    ofs << "," << email;
}

std::string Administrator::getType() const
{
    return "Administrator";
}

Administrator* Administrator::loadFromFile(const std::string& line)
{
    std::vector<std::string> parts = split(line, ',');

    if (parts.size() < 5)
        throw std::runtime_error("Invalid Administrator data format");

    const std::string username = parts[0];
    const std::string password = parts[1];
    const std::chrono::year_month_day ymd = parseDate(parts[2]);
    const std::time_t lastLogin = static_cast<std::time_t>(std::stoll(parts[3]));
    const std::string email = parts[4];

    Administrator* admin = new Administrator(username, password, email);
    admin->ymd = ymd;
    admin->getLastLogInDate() = lastLogin; //must do it with a setter and not with a getter

    return admin;
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
