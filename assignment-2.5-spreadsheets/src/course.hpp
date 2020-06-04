#ifndef COURSE_HPP
#define COURSE_HPP

#include "xstring.hpp"

struct Course
{
        lab::xstring code;
        lab::xstring name;

        Course(const lab::xstring& code, const lab::xstring& name)
            :code(code), name(name) {}
};

#endif /* COURSE_HPP */
