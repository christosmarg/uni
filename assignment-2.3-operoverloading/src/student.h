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

		inline bool operator== (const Student& s) const	{return (this->semester == s.semester)	? true : false;}
		inline bool operator!= (const Student& s) const	{return (this->semester != s.semester)	? true : false;}
		inline bool operator< (const Student& s)  const	{return (this->semester < s.semester)	? true : false;}
		inline bool operator<= (const Student& s) const	{return (this->semester <= s.semester)	? true : false;}
		inline bool operator> (const Student& s)  const	{return (this->semester > s.semester)	? true : false;}
		inline bool operator>= (const Student& s) const	{return (this->semester >= s.semester)	? true : false;}

		inline const char *get_AM(void) const {return this->AM;}
		inline const std::string& get_name(void) const {return this->name;}
		inline unsigned int get_semester(void) const {return this->semester;}
		inline unsigned int get_psubj(void) const {return this->psubj;}
		inline float *get_grades(void) const {return (this->psubj > 0) ? this->grades : nullptr;}
		inline Subject **get_submitted_subjects(void) const {return this->ssubj;}
		inline unsigned int get_num_submitted_subjects(void) const {return this->nssubj;}

		inline void set_AM(const char *AM) {this->AM = convert_AM(AM);}
		inline void set_name(const std::string& name) {this->name = name;}
		inline void set_semester(unsigned int semester) {this->semester = semester;}
		inline void set_psubj(unsigned int psubj) {this->psubj = psubj;}
		inline void set_grades(float *grades) {this->grades = convert_PSG(grades);}
		inline void set_num_submitted_subjects(unsigned int nssubj) {this->nssubj = nssubj;}

		void set_submitted_subjects(Subject **ssubj);
		char *convert_AM(const char *AM);
		float *convert_PSG(const float *grades);
		void add_grade(float grade);
		void detailed_print() const;
		float calc_average() const;
};

#endif /* STUDENT_H */
