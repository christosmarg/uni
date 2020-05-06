#ifndef XSTRING_H
#define XSTRING_H

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <vector>

namespace lab {
class xstring
{
	private:
		std::vector<char> str;

	public:
		xstring();
		xstring(const char *s);
		~xstring();
		
		xstring	 operator=	(const xstring& s);
		xstring	 operator=	(const char *s);
		xstring  operator+	(const xstring& s);
		xstring  operator+	(const char *s);
		xstring& operator+=	(const xstring& s);
		xstring& operator+=	(const char *s);
		xstring& operator+=	(char c);
		bool operator==	(const xstring& s)	const;
		bool operator== (const char *s)		const;
		bool operator!=	(const xstring& s)	const;
		bool operator!= (const char *s)		const;
		bool operator<	(const xstring& s)	const;
		bool operator<	(const char *s)		const;
		bool operator<=	(const xstring& s)	const;
		bool operator<=	(const char *s)		const;
		bool operator>	(const xstring& s)	const;
		bool operator>	(const char *s)		const;
		bool operator>=	(const xstring& s)	const;
		bool operator>=	(const char *s)		const;
		char& operator[] (std::size_t i);
		friend std::ostream& operator<< (std::ostream& stream, const xstring& s);
		friend std::istream& operator>> (std::istream& stream, const xstring& s);

		xstring& append(const xstring& s);
		xstring& append(const xstring& s, std::size_t i);
		xstring& append(const char *s);
		xstring& append(const char *s, std::size_t i);
		xstring& append(char c);

		char *cstr() const;
		std::size_t len() const;
		void strclear();
	
	private:
		void store(const char *s);
		void store(const char *s, std::size_t i);
		bool strempty(const char *s) const;
};

std::istream& getline(std::istream& stream, xstring& s, char delim = '\n');
template<typename T> xstring to_xstr(T val);
template<typename T> xstring to_xstr(const char *fs, T val);
template<typename T> const char *getformat();

template<typename T>
xstring to_xstr(T val)
{
	char buf[25];
	snprintf(buf, sizeof(buf), getformat<T>(), val);
	return xstring(buf);
}

template<typename T>
xstring to_xstr(const char *fs, T val)
{
	char buf[25];
	snprintf(buf, sizeof(buf), fs, val);
	return xstring(buf);
}
}

#endif /* XSTRING_H */
