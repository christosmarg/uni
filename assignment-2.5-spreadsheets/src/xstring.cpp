#include "xstring.h"

namespace lab {
xstring::xstring()
	:str(new char[1]), len(0)
{
	str[0] = '\0';
}

xstring::xstring(const char *s)
	:str(conv(s)), len(strlen(s)) {}

xstring::xstring(const xstring& s)
{
	if (!s.empty())
	{
		str = conv(s.str);
		len = s.len;
	}
	else
	{
		len = 0;
		str = new char[1];
	}
}

xstring::~xstring()
{
	delete[] str;
}

xstring xstring::operator= (const xstring& s)
{
	if (this == &s) return *this;
	if (!s.empty())
	{
		if (!empty()) delete[] str;
		str = conv(s.str);
		len = s.len;
	}
	else
	{
		str = new char[1];
		len = 0;
	}
	return *this;
}

xstring	xstring::operator= (const char *s)
{
	if (!empty()) delete[] str;
	str = conv(s);
	len = length();
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
	append(s.str);
	return *this;	
}

xstring& xstring::operator+= (const char *s)
{
	append(s);
	return *this;
}

xstring& xstring::operator+= (char c)
{
	push_back(c);
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

char& xstring::operator[] (std::size_t i) const
{
	if (i >= len) throw std::runtime_error("Out of bounds.");
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
	if (!s.empty())
	{
		resize(s.len);
		strcat(str, s.str);
	}
	len = length();
	return *this;
}

xstring& xstring::append(const xstring& s, std::size_t i)
{
	if (!s.empty() && i < len)
	{
		char *tmp1 = new char[i + 1];
		char *tmp2 = new char[len - i + 1];
		std::copy(str, str + i + 1, tmp1);
		std::copy(str + i, str + len + 1, tmp2);
		resize(s.len);
		std::copy(tmp1, tmp1 + i + 1, str);
		std::copy(s.str, s.str + s.len + 1, str + i);
		std::copy(tmp2, tmp2 + len - i + 1, str + s.len + i); 
		len = length();
		str[len] = '\0';
		delete[] tmp1;
		delete[] tmp2;
	}
	return *this;
}

xstring& xstring::append(const char *s)
{
	if (!strempty(s))
	{
		resize(strlen(s));
		strcat(str, s);
	}
	len = length();
	return *this;
}

xstring& xstring::append(const char *s, std::size_t i)
{
	if (!strempty(s) && i < len)
	{
		char *tmp1 = new char[i + 1];
		char *tmp2 = new char[len - i + 1];
		std::copy(str, str + i + 1, tmp1);
		std::copy(str + i, str + len + 1, tmp2);
		resize(strlen(s));
		std::copy(tmp1, tmp1 + i + 1, str);
		std::copy(s, s + strlen(s) + 1, str + i);
		std::copy(tmp2, tmp2 + len - i + 1, str + strlen(s) + i); 
		len = length();
		str[len] = '\0';
		delete[] tmp1;
		delete[] tmp2;
	}
	return *this;
}

xstring& xstring::append(char c)
{
	push_back(c);
	return *this;
}

void xstring::push_back(char c)
{
	resize(1);
	str[len] = c;
	str[len+1] = '\0';
	len = length();
}

void xstring::pop_back()
{
	if (len - 1 > 0)
	{
		char *tmp = new char[len];
		std::copy(str, str + len, tmp);
		delete[] str;
		tmp[len - 1] = '\0';
		str = tmp;
		len--;
	}
	else if (len - 1 == 0)
	{
		delete[] str;
		str = new char[1];
		str[0] = '\0';
	}
	else return;
}

void xstring::replace(std::size_t i, char c)
{
	if (i < len) str[i] = c;	
}

bool xstring::find(const xstring& s) const
{
	return (strstr(this->cstr(), s.cstr()) != nullptr);
}

bool xstring::find(const char *s) const
{
	return (strstr(this->cstr(), s) != nullptr);
}

char *xstring::cstr() const
{
	return str;
}

char& xstring::front() const
{
	return str[0];
}

char& xstring::back() const
{
	if (!this->empty()) return str[len-1];
	else return str[0];
}

std::size_t xstring::length() const
{
	return strlen(str);
}

bool xstring::empty() const
{
	return len == 0;
}

void xstring::clear()
{
	if (!this->empty()) delete[] str;
	str = new char[1];
	str[0] = '\0';
	//*this = "";
	len = 0;
}

void xstring::resize(std::size_t n)
{
	if (!this->empty())
	{
		std::size_t l = len + n;
		char *tmp = new char[l + 1];
		std::copy(str, str + len + 1, tmp);
		delete[] str;
		str = tmp;
		len = length();
	}
}

char *xstring::conv(const char *s) const
{
	std::size_t l = strlen(s);
	char *tmp = new char[l + 1];
	std::copy(s, s + l+1, tmp);
	return tmp;
}

bool xstring::strempty(const char *s) const
{
	return strlen(s) == 0;
}

std::istream& getline(std::istream& stream, xstring& s, char delim)
{
	char c;
	s.clear();
	while (stream.get(c) && c != '\n')
	{
		if (c == delim) break;
		else s.push_back(c);
	}
	return stream;
}
}
