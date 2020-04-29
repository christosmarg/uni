#include "manufacturer.h"

Manufacturer::Manufacturer()
	:serialnum(nullptr), name(nullptr), email("") {}

Manufacturer::Manufacturer(const char *serialnum, const char *name,
		const std::string& email)
	:serialnum(convstr(serialnum)), name(convstr(name)), email(email) {}

Manufacturer::Manufacturer(const Manufacturer& m)
	:serialnum(convstr(m.serialnum)), name(convstr(m.name)), email(m.email) {}

Manufacturer::~Manufacturer()
{
	if (serialnum != nullptr) delete[] serialnum;
	if (name != nullptr) delete[] name;
}

char *Manufacturer::convstr(const char *str)
{
	int len = strlen(str);
	char *tmp = new char[len + 1];
	std::copy(str, str + len + 1, tmp);
	return tmp;
}

const char *Manufacturer::get_serialnum() const
{
	return serialnum;
}

const char *Manufacturer::get_name() const
{
	return name;
}

const std::string& Manufacturer::get_email() const
{
	return email;
}
