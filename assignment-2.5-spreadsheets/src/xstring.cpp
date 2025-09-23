#include "xstring.h"

template<> const char *getformat<int>() {return "%d";}
template<> const char *getformat<float>() {return "%f";}
template<> const char *getformat<double>() {return "%f";}

xstring::xstring()
	:str(new char[1]), len(0) {}

xstring::xstring(const char *s)
	:str(conv(s)), len(strlen(s)) {}

xstring::xstring(const xstring& s)
{
	if (!this->empty())
	{
		str = conv(s.str);
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
	if (!this->empty())
	{
		len = 0;
		delete[] str;
	}
}

xstring xstring::operator= (const xstring& s)
{
	if (this == &s) return *this;
	if (!s.empty())
	{
		if (!this->empty()) delete[] str;
		str = conv(s.str);
		len = strlen(str);
	}
	else
	{
		str = nullptr;
		len = 0;
	}
	return *this;
}

xstring	xstring::operator= (const char *s)
{
	if (!this->empty()) delete[] str;
	str = conv(s);
	len = strlen(str);
	return *this;
}

xstring xstring::operator+ (const xstring& s)
{
	return xstring(strcat(this->str, s.str));
}

xstring xstring::operator+ (const char *s)
{
	return xstring(strcat(this->str, s));
}

xstring& xstring::operator+= (const xstring& s)
{
	if (!this->empty())
	{
		resize(s.str);
		strcat(str, s.str);
	}
	else str = conv(s.str);
	len = strlen(str);
	return *this;	
}

xstring& xstring::operator+= (const char *s)
{
	if (!this->empty())
	{
		resize(s);
		strcat(str, s);
	}
	else str = conv(s);
	len = strlen(str);
	return *this;
}

bool xstring::operator== (const xstring& s) const
{
	return strcmp(this->str, s.str) == 0;
}

bool xstring::operator== (const char *s) const
{
	return strcmp(this->str, s) == 0;
}

bool xstring::operator!= (const xstring& s) const
{
	return strcmp(this->str, s.str) != 0;
}

bool xstring::operator!= (const char *s) const
{
	return strcmp(this->str, s) != 0;
}

bool xstring::operator< (const xstring& s) const
{
	return strlen(this->str) < strlen(s.str);
}

bool xstring::operator< (const char *s) const
{
	return strlen(this->str) < strlen(s);
}

bool xstring::operator<= (const xstring& s) const
{
	return strlen(this->str) <= strlen(s.str);
}

bool xstring::operator<= (const char *s) const
{
	return strlen(this->str) <= strlen(s);
}

bool xstring::operator> (const xstring& s) const
{
	return strlen(this->str) > strlen(s.str);
}

bool xstring::operator> (const char *s) const
{
	return strlen(this->str) > strlen(s);
}

bool xstring::operator>= (const xstring& s) const
{
	return strlen(this->str) >= strlen(s.str);
}

bool xstring::operator>= (const char *s) const
{
	return strlen(this->str) >= strlen(s);
}

char& xstring::operator[] (int i) const
{
	if (i >= len)
	{
		std::cerr << "Out of bounds." << std::endl;
		exit(1);
	}
	return str[i];	
}

std::ostream& operator<< (std::ostream& stream, const xstring& s)
{
	return stream << s.str;
}

std::istream& operator>> (std::istream& stream, const xstring& s)
{
	return stream >> s.str;
}

xstring& xstring::append(const xstring& s)
{
	if (!s.empty()) *this += s;
	return *this;
}

xstring& xstring::append(const xstring& s, int i)
{

}

xstring& xstring::append(const char *s)
{
	if (!strempty(s)) *this += s;
	return *this;
}

xstring& xstring::append(const char *s, int i)
{

}

char *xstring::cstr() const
{
	return str;
}

char& xstring::last() const
{
	if (!this->empty()) return str[len-1];
}

std::size_t xstring::size()
{
	len = strlen(str);
	return len; 
}

bool xstring::empty() const
{
	return str == nullptr;
}

bool xstring::strempty(const char *s) const
{
	return s == nullptr;
}

void xstring::clear()
{
	if (!this->empty()) delete[] str;
	str = nullptr;
	len = 0;
}

char *xstring::conv(const char *s)
{
	int sl = strlen(s);
	char *tmp = new char[sl+1];
	std::copy(s, s + sl+1, tmp);
	return tmp;
}

void xstring::resize(const char *s)
{
	if (!this->empty())
	{
		int l = len + strlen(s);
		char *tmp = new char[l + 1];
		std::copy(str, str + len+1, tmp);
		delete[] str;
		str = tmp;
		len = strlen(str);
	}
}
