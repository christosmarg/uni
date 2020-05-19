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

		bool operator== (const Student& s) const;
		bool operator!= (const Student& s) const;
		bool operator<	(const Student& s) const;
		bool operator<= (const Student& s) const;
		bool operator>	(const Student& s) const;
		bool operator>= (const Student& s) const;

		const char *get_AM() const;
		const std::string& get_name() const;
		unsigned int get_semester() const;
		unsigned int get_pcourses() const; 
		float *get_grades() const;
		Course **get_submitted_courses() const; 
		unsigned int get_num_submitted_courses() const;

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
