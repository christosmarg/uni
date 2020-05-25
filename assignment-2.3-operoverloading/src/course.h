#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>

class Course
{
    private:
        std::string code;           // Course code
        std::string cname;          // Course name
        unsigned int csemester;     // Corresponding semester of course

    public:
        Course();
        Course(const std::string& code, const std::string& cname, unsigned int csemester);
        Course(const Course& s);

        const std::string& get_code() const;
        const std::string& get_cname() const;
        constexpr unsigned int get_csemester() const {return csemester;}

        void set_code(const std::string& code);
        void set_cname(const std::string& cname);
        void set_csemester(unsigned int csemester);
};

#endif /* COURSE_H */
