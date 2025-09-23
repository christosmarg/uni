#ifndef APP_H
#define APP_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "course.h"
#include "student.h"
#include "xstring.h"

typedef std::map<lab::xstring, lab::xstring> equivalencies;

class App
{
	private:
		std::map<lab::xstring, Course *> courses;
		std::map<lab::xstring, Student *> studs;
		std::map<Student *, std::map<Course *, float>> data;
		equivalencies eqvs;

	public:
		App();
		~App();

		template<typename T> bool import_data(const char *fpath);
		void store_data();
		void analyze();
		
	private:
		bool valid_path(const char *fpath);
		const lab::xstring err_csv(const char *fpath);
		const lab::xstring err_read(const char *fpath);
		const lab::xstring err_write(const char *fpath);
		template<typename T> void dealloc(std::map<lab::xstring, T *>& vec);
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
					courses.insert(std::make_pair(code, new Course(code, name)));
				}
				else if (std::is_same<T, Student>::value)
				{
					lab::xstring AM, lname, fname;
					lab::getline(f, AM, ';');
					lab::getline(f, lname, ';');
					lab::getline(f, fname);
					if (f.eof()) break;
					studs.insert(std::make_pair(AM, new Student(AM, lname, fname)));
				}
				else if (std::is_same<T, equivalencies>::value)
				{
					lab::xstring newcurr, oldcurr;
					lab::getline(f, newcurr, ';');
					lab::getline(f, oldcurr);
					if (f.eof()) break;
					eqvs.insert(std::make_pair(newcurr, oldcurr));
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
App::dealloc(std::map<lab::xstring, T *>& vec)
{
	for (auto& v : vec)
		if (v.second != nullptr)
			delete v.second;
	if (!vec.empty())
		vec.clear();
}

#endif /* APP_H */
