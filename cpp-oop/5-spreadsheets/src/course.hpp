#ifndef COURSE_HPP
#define COURSE_HPP

#include "xstring.hpp"

struct Course
{
        lab::xstring code;
        lab::xstring name;
        bool four_year;

        Course(const lab::xstring& code, const lab::xstring& name,
               const bool four_year)
            :code(code), name(name), four_year(four_year) {}
};

#endif /* COURSE_HPP */
