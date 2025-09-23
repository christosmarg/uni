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

		const std::string& get_code() const;
		const std::string& get_sname() const;
		unsigned int get_subjsemester() const;

		void set_code(const std::string& code);
		void set_sname(const std::string& sname);
		void set_subjsemester(unsigned int subjsemester);
};

#endif /* SUBJECT_H */
