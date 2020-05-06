#ifndef COURSE_H
#define COURSE_H

#include "xstring.h"

class Course
{
	private:
		lab::xstring code;
		lab::xstring name;

	public:
		Course(const lab::xstring& code, const lab::xstring& name);
};

#endif /* COURSE_H */
