#include "xstring.h"

xstring::xstring()
	:str(nullptr), len(0) {}

xstring::xstring(const char *str)
	:str(transfer(str)), len(strlen(str)) {}

xstring::xstring(const xstring& s)
{
	if (s.str != nullptr)
	{
		str = transfer(s.str);
		len = strlen(str);
	}
	else
	{
		str = nullptr;
		len = 0;
	}
}

xstring::~xstring()
{
	delete[] str;
}

void xstring::operator+= (const char *ns)
{
	if (str != nullptr) strcat(str, ns);
	else str = transfer(ns);
	len = strlen(str);
}

xstring xstring::operator= (const xstring& s)
{
	if (this == &s) return *this;
	if (s.str != nullptr)
	{
		if (str != nullptr) delete[] str;
		str = transfer(s.str);
		len = strlen(str);
	}
	else
	{
		str = nullptr;
		len = 0;
	}
	return *this;
}

std::ostream& operator<< (std::ostream& stream, const xstring& s)
{
	return stream << s.str;
}

int xstring::size() const
{
	return len; 
}

void xstring::clear()
{
	if (str != nullptr) delete[] str;
	str = nullptr;
	len = 0;
}

char *xstring::transfer(const char *str)
{
	int sl = strlen(str);
	char *tmp = new char[sl+1];
	std::copy(str, str + sl+1, tmp);
	return tmp;
}
