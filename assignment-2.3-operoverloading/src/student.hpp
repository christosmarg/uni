#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>

#include "course.hpp"

class Student
{
    private:
        char *id;              // id
        std::string name;      // Name
        unsigned int semester; // Current semester
        unsigned int pcourses; // Passed courses
        float *grades;         // Grades
        Course **sc;           // Submitted courses
        unsigned int nsc;      // Number of submitted courses 

    public:
        Student(const char *id, const std::string& name);
        Student(const char *id, const std::string& name,
                const unsigned int semester);
        Student(const char *id, const std::string& name,
                const unsigned int semester,
                const unsigned int pcourses, const float *grades);
        Student(const Student& s);
        ~Student();

        void operator+= (Course *c);
        Student operator= (const Student& s);

		/* 
		 * The function below are marked as constexpr just so they 
		 * can be computed at compile time since everything is hardcoded.
		 */
        constexpr bool operator== (const Student& s) const {return this->semester == s.semester;}
        constexpr bool operator!= (const Student& s) const {return this->semester != s.semester;}
        constexpr bool operator<  (const Student& s) const {return this->semester <  s.semester;}
        constexpr bool operator<= (const Student& s) const {return this->semester <= s.semester;}
        constexpr bool operator>  (const Student& s) const {return this->semester >  s.semester;}
        constexpr bool operator>= (const Student& s) const {return this->semester >= s.semester;}

        const std::string& get_name() const;
        constexpr const char *get_id() const {return this->id;}
        constexpr const unsigned int get_semester() const {return this->semester;}
        constexpr const unsigned int get_pcourses() const {return this->pcourses;}
        constexpr float *get_grades() const
            {return (this->pcourses > 0) ? this->grades : nullptr;}
        constexpr Course **get_submitted_courses() const {return this->sc;}
        constexpr const unsigned int get_num_submitted_courses() const {return this->nsc;}

        void set_id      (const char *id);
        void set_name    (const std::string& name);
        void set_semester(const unsigned int semester);
        void set_pcourses(const unsigned int pcourses);
        void set_grades  (const float *grades);
        void set_num_submitted_courses(const unsigned int nsc);
        void set_submitted_courses(Course **sc);

        void add_grade(const float grade);
        void detailed_print() const;

    private:
        template<typename T> T *conv(const T *arr, std::size_t len) const;
        template<typename T> T *resize(const T *arr, std::size_t len);
        constexpr std::size_t len(const char *s) const {return std::strlen(s) + 1;}
        float avg() const;
};

/* 
 * Makes a copy of a given array of type T and returns a temporary array
 * which is meant to be stored in a member variable.
 * If the array is empty it returns nullptr.
 */
template<typename T> T *
Student::conv(const T *arr, std::size_t len) const
{
    if (arr != nullptr)
    {
        T *tmp = new T[len];
        std::memcpy(tmp, arr, sizeof(T) * len);
        return tmp;
    }
    else return nullptr;
}

template<typename T> T *
Student::resize(const T *arr, std::size_t len)
{
    T *tmp = new T[len+1];
    if (arr != nullptr)
    {
        std::memcpy(tmp, arr, sizeof(T) * len);
        delete[] arr;
    }
    return tmp;
}

#endif /* STUDENT_HPP */
