#ifndef COURSE_H
#define COURSE_H

#include "xstring.h"

class Course
{
    private:
        lab::xstring code;
        lab::xstring name;

    public:
        Course(const lab::xstring& code, const lab::xstring& name)
            :code(code), name(name) {}

        inline constexpr const lab::xstring& get_code() const {return code;}
        inline constexpr const lab::xstring& get_name() const {return name;}
};

#endif /* COURSE_H */
