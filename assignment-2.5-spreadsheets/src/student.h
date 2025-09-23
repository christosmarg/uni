#ifndef STUDENT_H
#define STUDENT_H

#include "xstring.h"

class Student
{
    private:
        lab::xstring id;
        lab::xstring lname;
        lab::xstring fname;

    public:
        Student(const lab::xstring& id,
                const lab::xstring& lname,
                const lab::xstring& fname)
            :id(id), lname(lname), fname(fname) {}

        inline constexpr const lab::xstring& get_id()    const {return id;}
        inline constexpr const lab::xstring& get_lname() const {return lname;}
        inline constexpr const lab::xstring& get_fname() const {return fname;}
};

#endif /* STUDENT_H */
