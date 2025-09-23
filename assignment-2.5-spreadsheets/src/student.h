#ifndef STUDENT_H
#define STUDENT_H

#include "xstring.h"

struct Student
{
		lab::xstring id;
		lab::xstring lname;
		lab::xstring fname;

		Student(const lab::xstring& id,
				const lab::xstring& lname,
				const lab::xstring& fname)
			:id(id), lname(lname), fname(fname) {}
};

#endif /* STUDENT_H */
