#ifndef XSTRING_H
#define XSTRING_H

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string.h>

class xstring
{
	private:
		char *str;
		int len;

		char *conv(const char *s);
		void resize(const char *s);
		bool strempty(const char *s) const;

	public:
		xstring();
		xstring(const char *s);
		xstring(const xstring& s);
		~xstring();
		
		xstring	 operator=	(const xstring& s);
		xstring	 operator=	(const char *s);
		xstring  operator+	(const xstring& s);
		xstring  operator+	(const char *s);
		xstring& operator+=	(const xstring& s);
		xstring& operator+=	(const char *s);
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
		char& operator[] (int i) const;
		friend std::ostream& operator<< (std::ostream& stream, const xstring& s);
		friend std::istream& operator>> (std::istream& stream, const xstring& s);

		xstring& append(const xstring& s);
		xstring& append(const xstring& s, int i);
		xstring& append(const char *s);
		xstring& append(const char *s, int i);

		char *cstr() const;
		char& last() const;
		std::size_t size();
		bool empty() const;
		void clear();
};

template<typename T> xstring tostr(T val);
template<typename T> const char *getformat();
template<typename T>
xstring tostr(T val)
{
	char buf[25];
	snprintf(buf, sizeof(buf), getformat<T>(), val);
	return xstring(buf);
}

#endif /* XSTRING_H */
