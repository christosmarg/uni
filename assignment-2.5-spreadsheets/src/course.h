#ifndef COURSE_H
#define COURSE_H

#include "xstring.h"

struct Course
{
        lab::xstring code;
        lab::xstring name;

        Course(const lab::xstring& code, const lab::xstring& name)
            :code(code), name(name) {}
};

#endif /* COURSE_H */
