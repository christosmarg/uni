#ifndef STUDENT_H
#define STUDENT_H

#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>

#include "course.h"

class Student
{
	private:
		char *id;				// id
		std::string name;		// Name
		Course **sc;			// Submitted courses
		unsigned int nsc;		// Number of submitted courses 
		unsigned int semester;	// Current semester
		unsigned int pcourses;	// Passed courses
		float *grades;			// Grades
		std::size_t size;

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

		constexpr bool operator== (const Student& s) const {return this->semester == s.semester;}
		constexpr bool operator!= (const Student& s) const {return this->semester != s.semester;}
		constexpr bool operator<  (const Student& s) const {return this->semester <  s.semester;}
		constexpr bool operator<= (const Student& s) const {return this->semester <= s.semester;}
		constexpr bool operator>  (const Student& s) const {return this->semester >  s.semester;}
		constexpr bool operator>= (const Student& s) const {return this->semester >= s.semester;}

		const std::string& get_name() const;
		constexpr const char *get_id() const {return this->id;}
		constexpr unsigned int get_semester() const {return this->semester;}
		constexpr unsigned int get_pcourses() const {return this->pcourses;}
		constexpr float *get_grades() const {return (this->pcourses > 0) ? this->grades : nullptr;}
		constexpr Course **get_submitted_courses() const		 {return this->sc;}
		constexpr unsigned int get_num_submitted_courses() const {return this->nsc;}

		void set_id		 (const char *id);
		void set_name	 (const std::string& name);
		void set_semester(const unsigned int semester);
		void set_pcourses(const unsigned int pcourses);
		void set_grades	 (const float *grades);
		void set_num_submitted_courses(const unsigned int nsc);
		void set_submitted_courses(Course **sc);

		void add_grade(const float grade);
		void detailed_print() const;

	private:
		char  *convid(const char *id);
		float *convpsg(const float *grades);
		float  avg() const;
};

#endif /* STUDENT_H */
