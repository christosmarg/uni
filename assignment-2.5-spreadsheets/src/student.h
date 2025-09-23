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

		constexpr const lab::xstring& get_AM()    const {return AM;}
		constexpr const lab::xstring& get_lname() const {return	lname;}
		constexpr const lab::xstring& get_fname() const {return fname;}
};

#endif /* STUDENT_H */
