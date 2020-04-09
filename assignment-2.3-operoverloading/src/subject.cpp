#include "subject.h"


Subject::Subject() {std::cout << "Constructor 1" << std::endl;}

Subject::Subject(const std::string& code, const std::string& sname, unsigned int subjsemester)
	:code(code), sname(sname), subjsemester(subjsemester) {std::cout << "Constructor 2" << std::endl;}

Subject::Subject(const Subject& s)
	:code(s.code), sname(s.sname), subjsemester(s.subjsemester) {std::cout << "Copy Constructor" << std::endl;}
