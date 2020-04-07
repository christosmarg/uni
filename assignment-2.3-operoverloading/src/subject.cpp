#include "subject.h"


Subject::Subject() {}

Subject::Subject(const std::string& code, const std::string& sname, unsigned int subjsemester)
	:code(code), sname(sname), subjsemester(subjsemester) {}

Subject::Subject(const Subject& s)
	:code(s.code), sname(s.sname), subjsemester(s.subjsemester) {}

Subject::~Subject() {}
