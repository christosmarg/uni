#ifndef STUDENT_H
#define STUDENT_H

#include "xstring.h"

class Student
{
	private:
		lab::xstring id;
		lab::xstring lname;
		lab::xstring fname;

	public:
		Student(const lab::xstring& id,
				const lab::xstring& lname,
				const lab::xstring& fname);

		constexpr const lab::xstring& get_id()    const {return id;}
		constexpr const lab::xstring& get_lname() const {return	lname;}
		constexpr const lab::xstring& get_fname() const {return fname;}
};

#endif /* STUDENT_H */
