#include "errlog.h"

ErrLog::ErrLog() {fclear();}

void
ErrLog::fclear() const
{
	std::ofstream f;
	f.open(fpath, std::ofstream::trunc);
	f << "Type;Info;Err" << std::endl;
	f.close();
}

void
ErrLog::write(ErrType type, const lab::xstring& s) const
{
	std::ofstream f;
	f.open(fpath, std::ios_base::app);
	switch(type)
	{
		case ErrType::STUDENT_MISSING:
			f << "Student;" << s << ";Missing." << std::endl;
			break;
		case ErrType::COURSE_MISSING:
			f << "Course;" << s << ";Missing." << std::endl;
			break;
		case ErrType::GRADE_DUPLICATE:
			break;
		case ErrType::MULTIPLE_GRADES:
			break;
	}
	f.close();
}