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

		const lab::xstring& get_code() const;
		const lab::xstring& get_name() const;
};

#endif /* COURSE_H */
