#ifndef XSTRING_H
#define XSTRING_H

#include <algorithm>
#include <iostream>
#include <string.h>

class xstring
{
	private:
		char *str;
		int len;

		char *transfer(const char *str);

	public:
		xstring();
		xstring(const char *str);
		xstring(const xstring& s);
		~xstring();
		
		void operator+=	(const char *ns);
		xstring operator= (const xstring& s);
		friend std::ostream& operator<< (std::ostream& stream, const xstring& s);

		int size() const;
		void clear();
};

#endif /* XSTRING_H */
