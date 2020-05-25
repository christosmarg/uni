#include "manufacturer.h"

Manufacturer::Manufacturer()
    :serialnum(nullptr), name(nullptr), email("") {}

Manufacturer::Manufacturer(const char *serialnum, const char *name,
        const std::string& email)
    :serialnum(convstr(serialnum)), name(convstr(name)), email(email)
{
    if (!std::strcmp(serialnum, ""))
        throw std::runtime_error("Empty manufacturer serial number.");
    if (!std::strcmp(name, ""))
        throw std::runtime_error("Empty manufacturer name.");
    if (email.empty() || email.find("@") == std::string::npos)
    {
        std::string err = "Invalid email. Empty email/Missing \'@\'";
        throw std::runtime_error(err);
    }
}

Manufacturer::Manufacturer(const Manufacturer& m)
    :serialnum(convstr(m.serialnum)), name(convstr(m.name)), email(m.email) {}

Manufacturer::~Manufacturer()
{
    if (serialnum != nullptr) delete[] serialnum;
    if (name != nullptr) delete[] name;
}

char *
Manufacturer::convstr(const char *str)
{
    int len = std::strlen(str);
    char *tmp = new char[len + 1];
    std::copy(str, str + len + 1, tmp);
    return tmp;
}

void
Manufacturer::set_serialnum(const char *serialnum)
{
    if (this->serialnum != nullptr) delete[] serialnum;
    this->serialnum = convstr(serialnum);
}

void
Manufacturer::set_name(const char *name)
{
    if (this->name != nullptr) delete[] name;
    this->name = convstr(name);
}
