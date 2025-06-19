#include "UserFactory.h"

User* UserFactory::createUser(const std::string& username, const std::string& password, bool isAdmin)
{
    if (isAdmin)
        return new Administrator(username, password, username + "@library.com");
    else
        return new Reader(username, password);
}
