#include "student.h"

Student::Student(const lab::xstring& AM,
		const lab::xstring& lname,
		const lab::xstring& fname)
	:AM(AM), lname(lname), fname(fname) {}

const lab::xstring&
Student::get_AM() const
{
	return AM;
}

const lab::xstring&
Student::get_lname() const
{
	return lname;
}

const lab::xstring&
Student::get_fname() const
{
	return fname;
}
