#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>

#include "subject.h"

class Student
{
	private:
		char *AM;				// AM
		std::string name;		// Name
		Subject **ssubj;		// Submitted subjects
		unsigned int nssubj;	// Number of submitted subjects
		unsigned int semester;	// Current semester
		unsigned int psubj;		// Passed subjects
		float *grades;			// Grades
		int size;

	public:
		Student(const char *AM, const std::string& name);
		Student(const char *AM, const std::string& name, unsigned int semester);
		Student(const char *AM, const std::string& name, unsigned int semester,
				unsigned int psubj, const float *grades);
		Student(const Student& s);
		~Student();

		void operator+= (Subject *s);
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
		unsigned int get_psubj() const; 
		float *get_grades() const;
		Subject **get_submitted_subjects() const; 
		unsigned int get_num_submitted_subjects() const;

		void set_AM(const char *AM);
		void set_name(const std::string& name);
		void set_semester(unsigned int semester);
		void set_psubj(unsigned int psubj);
		void set_grades(float *grades);
		void set_num_submitted_subjects(unsigned int nssubj);
		void set_submitted_subjects(Subject **ssubj);

		void add_grade(float grade);
		void detailed_print() const;

	private:
		char *convert_AM(const char *AM);
		float *convert_PSG(const float *grades);
		float calc_average() const;
};

#endif /* STUDENT_H */
