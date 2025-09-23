#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "xstring.hpp"

struct Student
{
        lab::xstring id;
        lab::xstring lname;
        lab::xstring fname;

        Student(const lab::xstring& id,
                const lab::xstring& lname,
                const lab::xstring& fname)
            :id(id), lname(lname), fname(fname) {}
};

#endif /* STUDENT_HPP */
