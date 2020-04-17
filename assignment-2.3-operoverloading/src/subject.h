#ifndef SUBJECT_H
#define SUBJECT_H

#include <iostream>
#include <string>

class Subject
{
	private:
		std::string code;			// Subject code
		std::string sname;			// Subject name
		unsigned int subjsemester;	// Corresponding semester of subject

	public:
		Subject();
		Subject(const std::string& code, const std::string& sname, unsigned int subjsemester);
		Subject(const Subject& s);

		inline const std::string& get_code(void) const {return this->code;}
		inline const std::string& get_sname(void) const {return this->sname;}
		inline unsigned int get_subjsemester(void) const {return this->subjsemester;}

		inline void set_code(const std::string& code) {this->code = code;}
		inline void set_sname(const std::string& sname) {this->sname = sname;}
		inline void set_subjsemester(unsigned int subjsemester) {this->subjsemester = subjsemester;}
};

#endif /* SUBJECT_H */
