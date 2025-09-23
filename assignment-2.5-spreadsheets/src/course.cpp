#include "course.h"

Course::Course(const lab::xstring& code, const lab::xstring& name)
	:code(code), name(name) {}

const lab::xstring&
Course::get_code() const
{
	return code;
}

const lab::xstring&
Course::get_name() const
{
	return name;
}
