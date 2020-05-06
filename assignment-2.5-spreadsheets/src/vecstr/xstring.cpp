#include "xstring.h"

namespace lab {
xstring::xstring() {}

xstring::xstring(const char *s) {store(s);}

xstring::~xstring()
{
	if (!str.empty()) str.clear();
}

xstring xstring::operator= (const xstring& s)
{
	if (this == &s) return *this;
	if (!s.str.empty())
	{
		this->str.clear();
		store(s.cstr());
	}
	return *this;
}

xstring	xstring::operator= (const char *s)
{
	if (!strempty(s)) store(s);
	return *this;
}

xstring xstring::operator+ (const xstring& s)
{
	return xstring(strcat(this->cstr(), s.cstr()));
}

xstring xstring::operator+ (const char *s)
{
	return xstring(strcat(this->cstr(), s));
}

xstring& xstring::operator+= (const xstring& s)
{
	store(s.cstr());
	return *this;	
}

xstring& xstring::operator+= (const char *s)
{
	store(s);
	return *this;
}

xstring& xstring::operator+= (char c)
{
	str.push_back(c);
	return *this;
}

bool xstring::operator== (const xstring& s) const
{
	return strcmp(this->cstr(), s.cstr()) == 0;
}

bool xstring::operator== (const char *s) const
{
	return strcmp(this->cstr(), s) == 0;
}

bool xstring::operator!= (const xstring& s) const
{
	return strcmp(this->cstr(), s.cstr()) != 0;
}

bool xstring::operator!= (const char *s) const
{
	return strcmp(this->cstr(), s) != 0;
}

bool xstring::operator< (const xstring& s) const
{
	return strlen(this->cstr()) < strlen(s.cstr());
}

bool xstring::operator< (const char *s) const
{
	return strlen(this->cstr()) < strlen(s);
}

bool xstring::operator<= (const xstring& s) const
{
	return strlen(this->cstr()) <= strlen(s.cstr());
}

bool xstring::operator<= (const char *s) const
{
	return strlen(this->cstr()) <= strlen(s);
}

bool xstring::operator> (const xstring& s) const
{
	return strlen(this->cstr()) > strlen(s.cstr());
}

bool xstring::operator> (const char *s) const
{
	return strlen(this->cstr()) > strlen(s);
}

bool xstring::operator>= (const xstring& s) const
{
	return strlen(this->cstr()) >= strlen(s.cstr());
}

bool xstring::operator>= (const char *s) const
{
	return strlen(this->cstr()) >= strlen(s);
}

char& xstring::operator[] (std::size_t i)
{
	try {if (i >= str.size()) throw i;}
	catch (int i) {throw std::runtime_error("Out of bounds.");}
	return str[i];	
}

std::ostream& operator<< (std::ostream& stream, const xstring& s)
{
	return stream << s.cstr();
}

std::istream& operator>> (std::istream& stream, const xstring& s)
{
	return stream >> s.cstr();
}

void xstring::store(const char *s)
{
	str.insert(str.end(), s, s + strlen(s));
}

void xstring::store(const char *s, std::size_t i)
{
	str.insert(str.begin() + i, s, s + strlen(s));
}

xstring& xstring::append(const xstring& s)
{
	if (!strempty(s.cstr())) store(s.cstr());
	return *this;
}

xstring& xstring::append(const xstring& s, std::size_t i)
{
	if (!strempty(s.cstr())) store(s.cstr(), i);
	return *this;
}

xstring& xstring::append(const char *s)
{
	if (!strempty(s)) store(s);
	return *this;
}

xstring& xstring::append(const char *s, std::size_t i)
{
	if (!strempty(s)) store(s, i);
	return *this;
}

xstring& xstring::append(char c)
{
	str.push_back(c);
	return *this;
}

char *xstring::cstr() const
{
	if (!str.empty())
	{
		char *tmp = new char[str.size() + 1];
		for (std::size_t i = 0; i < str.size(); i++)
			tmp[i] = str[i];
		tmp[str.size()] = '\0';
		return tmp;
	}
	else return new char[1];
}

std::size_t xstring::len() const
{
	return str.size();
}

void xstring::strclear()
{
	str.clear();
}

bool xstring::strempty(const char *s) const
{
	return strlen(s) == 0;
}

std::istream& getline(std::istream& stream, xstring& s, char delim)
{
	char c;
	s.strclear();
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
