#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <string.h>

class Student
{
	private:
		char *AM;
		std::string name;
		std::string *submittedSubjects;
		unsigned int numSubmittedSubjects;
		unsigned int semester;
		unsigned int psubj;
		float *grades;
		int size;

	public:
		Student(const char *AM, const std::string& name);
		Student(const char *AM, const std::string& name, unsigned int semester);
		Student(const char *AM, const std::string& name, unsigned int semester,
				unsigned int psubj, const float *grades);
		Student(const Student& s);
		~Student();

		friend std::ostream& operator<< (std::ostream& stream, const Student& s);
		void operator+= (const std::string& s);
		Student& operator= (const Student& s);

		inline bool operator== (const Student& s) const	{return (this->semester == s.semester)	? true : false;}
		inline bool operator!= (const Student& s) const	{return (this->semester != s.semester)	? true : false;}
		inline bool operator< (const Student& s)  const	{return (this->semester < s.semester)	? true : false;}
		inline bool operator<= (const Student& s) const	{return (this->semester <= s.semester)	? true : false;}
		inline bool operator> (const Student& s)  const	{return (this->semester > s.semester)	? true : false;}
		inline bool operator>= (const Student& s) const	{return (this->semester >= s.semester)	? true : false;}

		inline const char *get_AM() const {return this->AM;}
		inline const std::string& get_name() const {return this->name;}
		inline unsigned int get_semester() const {return this->semester;}
		inline unsigned int get_psubj() const {return this->psubj;}
		float *get_grades() const;
		inline unsigned int get_num_submitted_subjects() const {return this->numSubmittedSubjects;}
		std::string *get_submitted_subjects() const;

		inline void set_AM(const char *AM) {this->AM = convert_AM(AM);}
		inline void set_name(const std::string& name) {this->name = name;}
		inline void set_semester(unsigned int semester) {this->semester = semester;}
		inline void set_psubj(unsigned int psubj) {this->psubj = psubj;}
		inline void set_grades(float *grades) {this->grades = convert_PSG(grades);}
		inline void set_num_submitted_subjects(unsigned int numSubmittedSubjects) {this->numSubmittedSubjects = numSubmittedSubjects;}
		void set_submitted_subjects(std::string* submittedSubjects);

		char *convert_AM(const char *AM);
		float *convert_PSG(const float *grades);
		void add_grade(float grade);
		void detailed_print() const;
		float calc_average() const;
};
