#ifndef GRADE_H
#define GRADE_H

#include "xstring.h"

class Grade
{
	private:
		lab::xstring AM;
		lab::xstring code;
		float grade;

	public:
		Grade(const lab::xstring& AM, const lab::xstring& code, float grade);
};

#endif /* GRADE_H */
