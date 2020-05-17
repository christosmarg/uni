#ifndef ERRLOG_H
#define ERRLOG_H

#include <fstream>
#include "xstring.h"

class ErrLog
{
	private:
		const char *fpath = "res/errlog.csv";

	public:
		enum class ErrType {
			STUDENT_MISSING,
			COURSE_MISSING,
			DIFFERENT_GRADES
		};

	public:
		ErrLog();

		void write(ErrType type, const lab::xstring& s) const;

	private:
		void fclear() const;
};

#endif /* ERRLOG_H */
