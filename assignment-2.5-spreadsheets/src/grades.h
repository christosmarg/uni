#ifndef GRADES_H
#define GRADES_H

#include "xstring.h"

class Grades
{
	private:
		lab::xstring AM;
		lab::xstring code;
		float grade;

	public:
		Grades(const lab::xstring& AM, const lab::xstring& code, float grade);
};

#endif
