#ifndef STUDENT_H
#define STUDENT_H

#include "xstring.h"

class Student
{
	private:
		lab::xstring AM;
		lab::xstring lname;
		lab::xstring fname;

	public:
		Student(const lab::xstring& AM,
				const lab::xstring& lname,
				const lab::xstring& fname);

		const lab::xstring& get_AM() const;
		const lab::xstring& get_lname() const;
		const lab::xstring& get_fname() const;
};

#endif /* STUDENT_H */
