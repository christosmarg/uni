#include "course.h"


Course::Course() {}

Course::Course(const std::string& code, const std::string& cname, unsigned int csemester)
    :code(code), cname(cname), csemester(csemester) {}

Course::Course(const Course& c)
    :code(c.code), cname(c.cname), csemester(c.csemester) {}

const std::string&
Course::get_code() const
{
    return this->code;
}

const std::string&
Course::get_cname() const
{
    return this->cname;
}

void
Course::set_code(const std::string& code)
{
    this->code = code;
}

void
Course::set_cname(const std::string& cname)
{
    this->cname = cname;
}

void
Course::set_csemester(unsigned int csemester)
{
    this->csemester = csemester;
}
