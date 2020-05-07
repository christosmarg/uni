#include "manufacturer.h"

Manufacturer::Manufacturer()
	:serialnum(nullptr), name(nullptr), email("") {}

Manufacturer::Manufacturer(const char *serialnum, const char *name,
		const std::string& email)
	:serialnum(convstr(serialnum)), name(convstr(name)), email(email)
{
	if (strcmp(serialnum, "") == 0)
		throw std::runtime_error("Empty manufacturer serial number.");
	if (strcmp(name, "") == 0)
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

void Manufacturer::set_serialnum(const char *serialnum)
{
	if (this->serialnum != nullptr) delete[] serialnum;
	this->serialnum = convstr(serialnum);
}

void Manufacturer::set_name(const char *name)
{
	if (this->name != nullptr) delete[] name;
	this->name = convstr(name);
}

void Manufacturer::set_email(const std::string& email)
{
	this->email = email;
}
