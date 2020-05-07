#ifndef XSTRING_H
#define XSTRING_H

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace lab {
class xstring
{
	private:
		char *str;
		std::size_t len;

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
		char& operator[] (std::size_t i)	const;
		friend std::ostream& operator<< (std::ostream& stream, const xstring& s);
		friend std::istream& operator>> (std::istream& stream, const xstring& s);

		xstring& append(const xstring& s);
		xstring& append(const xstring& s, std::size_t i);
		xstring& append(const char *s);
		xstring& append(const char *s, std::size_t i);
		xstring& append(char c);

		void push_back(char c);
		void pop_back();
		void replace(std::size_t i, char c);
		bool find(const xstring& s) const;
		bool find(const char *s) const;
		char *cstr() const;
		char& front() const;
		char& back() const;
		std::size_t length() const;
		bool empty() const;
		void clear();
	
	private:
		void resize(std::size_t n);
		char *conv(const char *s) const;
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

template<typename T>
const char *getformat()
{
	if (std::is_same<T, short>::value) return "%hi";
	if (std::is_same<T, int>::value) return "%d";
	if (std::is_same<T, long>::value) return "%ld";
	if (std::is_same<T, long long>::value) return "%lld";
	if (std::is_same<T, unsigned short>::value) return "%hu";
	if (std::is_same<T, unsigned int>::value) return "%u";
	if (std::is_same<T, unsigned long>::value) return "%lu";
	if (std::is_same<T, unsigned long>::value) return "%llu";
	if (std::is_same<T, float>::value) return "%f";
	if (std::is_same<T, double>::value) return "%f";
	if (std::is_same<T, long double>::value) return "%Lf";
}
}

#endif /* XSTRING_H */
