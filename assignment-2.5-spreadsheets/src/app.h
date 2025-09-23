#ifndef APP_H
#define APP_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "course.h"
#include "grade.h"
#include "student.h"
#include "xstring.h"

typedef std::map<lab::xstring, lab::xstring> equivalencies;

class App
{
	private:
		std::vector<Course *> courses;
		std::vector<Grade *> grades;
		std::vector<Student *> studs;
		equivalencies eqvs;

	public:
		App();
		~App();

		template<typename T> bool import_data(const char *fpath);
		
		const std::vector<Course *>& get_courses()	const;
		const std::vector<Grade *>& get_grades()	const;
		const std::vector<Student *>& get_studs()	const;
		const equivalencies& get_eqvs()				const;

	private:
		bool valid_path(const char *fpath);
		const lab::xstring err_csv(const char *fpath);
		const lab::xstring err_read(const char *fpath);
		const lab::xstring err_write(const char *fpath);
		template<typename T> void dealloc(std::vector<T *>& vec);
};

template<typename T> bool
App::import_data(const char *fpath)
{
	std::ifstream f;
	f.exceptions(std::ifstream::badbit);
	try
	{
		if (!valid_path(fpath))
			throw std::runtime_error(err_csv(fpath).cstr());
		f.open(fpath);
		if (f.is_open())
		{
			lab::xstring skip;
			lab::getline(f, skip);
			while (f.good())
			{
				if (std::is_same<T, Course>::value)
				{
					lab::xstring code, name;
					lab::getline(f, code, ';');
					lab::getline(f, name);
					if (f.eof()) break;
					courses.push_back(new Course(code, name));
				}
				else if (std::is_same<T, Grade>::value)
				{
					lab::xstring AM, code, grade;
					lab::getline(f, AM, ';');
					lab::getline(f, code, ';');
					lab::getline(f, grade);
					if (f.eof()) break;
					grades.push_back(new Grade(AM, code,
								std::atof(grade.cstr())));
				}
				else if (std::is_same<T, Student>::value)
				{
					lab::xstring AM, lname, fname;
					lab::getline(f, AM, ';');
					lab::getline(f, lname, ';');
					lab::getline(f, fname);
					if (f.eof()) break;
					studs.push_back(new Student(AM, lname, fname));
				}
				else if (std::is_same<T, equivalencies>::value)
				{
					lab::xstring newcurr, oldcurr;
					lab::getline(f, newcurr, ';');
					lab::getline(f, oldcurr);
					if (f.eof()) break;
					eqvs.emplace(newcurr, oldcurr);
				}
			}	
		}
		f.close();
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << err_read(fpath) << std::endl << e.what() << std::endl;
		return false;
	}
	return true;
}

template<typename T> void
App::dealloc(std::vector<T *>& vec)
{
	for (auto& v : vec)
		if (v != nullptr)
			delete v;
	if (!vec.empty())
		vec.clear();
}

#endif /* APP_H */
