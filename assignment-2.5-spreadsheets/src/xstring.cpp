#include "xstring.h"

namespace lab {
xstring::xstring()
	:str(new char[1]), len(0) {}

xstring::xstring(const char *s)
	:str(conv(s)), len(strlen(s)) {}

xstring::xstring(const xstring& s)
{
	if (!this->empty())
	{
		str = conv(s.str);
		len = size();
	}
	else
	{
		str = new char[1];
		len = 0;
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
		if (!this->empty()) delete[] str;
		str = conv(s.str);
		len = size();
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
	if (!this->empty()) delete[] str;
	str = conv(s);
	len = size();
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
	len = size();
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
	len = size();
	return *this;
}

xstring& xstring::operator+= (char c)
{
	if (!this->empty())
	{
		resize(1);
		str[len] = c;
	}
	else str = conv(c);
	// wtf
	len += size() + 1;
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

xstring& xstring::append(const xstring& s, std::size_t i)
{

}

xstring& xstring::append(const char *s)
{
	if (!strempty(s)) *this += s;
	return *this;
}

xstring& xstring::append(const char *s, std::size_t i)
{

}

xstring& xstring::append(char c)
{
	*this += c;
	return *this;
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
	return len == 0;
}

bool xstring::strempty(const char *s) const
{
	return strlen(s) == 0;
}

void xstring::clear()
{
	if (!this->empty()) delete[] str;
	str = new char[1];
	*this = "";
	len = 0;
}

char *xstring::conv(const char *s)
{
	std::size_t l = strlen(s);
	char *tmp = new char[l + 1];
	std::copy(s, s + l+1, tmp);
	return tmp;
}

char *xstring::conv(char c)
{
	// 2 for '\0'
	char *tmp = new char[1];
	tmp[0] = c;
	return tmp;
}

void xstring::resize(const char *s)
{
	if (!this->empty())
	{
		std::size_t l = len + strlen(s);
		char *tmp = new char[l + 1];
		std::copy(str, str + len+1, tmp);
		delete[] str;
		str = tmp;
		len = size();
	}
}

void xstring::resize(std::size_t n)
{
	if (!this->empty())
	{
		std::size_t l = len + n;
		char *tmp = new char[l + 1];
		std::copy(str, str + len+1, tmp);
		delete[] str;
		str = tmp;
		// wtf
		len = size();
	}
}

std::istream& getline(std::istream& stream, xstring& s)
{
	char c;
	s.clear();
	while (stream.get(c) && c != '\n')
		s.append(c);
	return stream;
}

std::istream& getline(std::istream& stream, xstring& s, char delim)
{
	char c;
	s.clear();
	while (stream.get(c) && c != '\n')
	{
		if (c == delim) break;
		else s.append(c);
	}
	return stream;
}

template<> const char *getformat<short>()	{return "%hi";}
template<> const char *getformat<int>()		{return "%d";}
template<> const char *getformat<long>()	{return "%ld";}
template<> const char *getformat<long long>() {return "%lld";}
template<> const char *getformat<unsigned short>()	{return "%hu";}
template<> const char *getformat<unsigned int>()	{return "%u";}
template<> const char *getformat<unsigned long>()	{return "%lu";}
template<> const char *getformat<unsigned long long>() {return "%llu";}
template<> const char *getformat<float>()	{return "%f";}
template<> const char *getformat<double>()	{return "%f";}
template<> const char *getformat<long double>()	{return "%Lf";}
}
