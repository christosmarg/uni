#include "subject.h"


Subject::Subject() {}

Subject::Subject(const std::string& code, const std::string& sname, unsigned int subjsemester)
	:code(code), sname(sname), subjsemester(subjsemester) {}

Subject::Subject(const Subject& s)
	:code(s.code), sname(s.sname), subjsemester(s.subjsemester) {}

const std::string& Subject::get_code() const
{
	return this->code;
}

const std::string& Subject::get_sname() const
{
	return this->sname;
}

unsigned int Subject::get_subjsemester() const
{
	return this->subjsemester;
}

void Subject::set_code(const std::string& code)
{
	this->code = code;
}

void Subject::set_sname(const std::string& sname)
{
	this->sname = sname;
}

void Subject::set_subjsemester(unsigned int subjsemester)
{
	this->subjsemester = subjsemester;
}
