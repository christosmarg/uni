#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>

#include "course.h"

class Student
{
	private:
		char *AM;				// AM
		std::string name;		// Name
		Course **sc;			// Submitted courses
		unsigned int nsc;		// Number of submitted courses 
		unsigned int semester;	// Current semester
		unsigned int pcourses;	// Passed courses
		float *grades;			// Grades
		int size;

	public:
		Student(const char *AM, const std::string& name);
		Student(const char *AM, const std::string& name, unsigned int semester);
		Student(const char *AM, const std::string& name, unsigned int semester,
				unsigned int pcourses, const float *grades);
		Student(const Student& s);
		~Student();

		void operator+= (Course *c);
		Student operator= (const Student& s);

		bool operator== (const Student& s) const {return this->semester == s.semester;}
		bool operator!= (const Student& s) const {return this->semester != s.semester;}
		bool operator<  (const Student& s) const {return this->semester <  s.semester;}
		bool operator<= (const Student& s) const {return this->semester <= s.semester;}
		bool operator>  (const Student& s) const {return this->semester >  s.semester;}
		bool operator>= (const Student& s) const {return this->semester >= s.semester;}

		const std::string& get_name() const;
		constexpr const char *get_AM() const {return this->AM;}
		constexpr unsigned int get_semester() const {return this->semester;}
		constexpr unsigned int get_pcourses() const {return this->pcourses;}
		constexpr float *get_grades() const {return (this->pcourses > 0) ? this->grades : nullptr;}
		constexpr Course **get_submitted_courses() const		 {return this->sc;}
		constexpr unsigned int get_num_submitted_courses() const {return this->nsc;}

		void set_AM(const char *AM);
		void set_name(const std::string& name);
		void set_semester(unsigned int semester);
		void set_pcourses(unsigned int pcourses);
		void set_grades(float *grades);
		void set_num_submitted_courses(unsigned int nsc);
		void set_submitted_courses(Course **sc);

		void add_grade(float grade);
		void detailed_print() const;

	private:
		char *convert_AM(const char *AM);
		float *convert_PSG(const float *grades);
		float calc_average() const;
};

#endif /* STUDENT_H */
