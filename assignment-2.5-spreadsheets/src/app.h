#ifndef APP_H
#define APP_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "course.h"
#include "grades.h"
#include "student.h"
#include "xstring.h"

class App
{
	private:
		std::vector<Course *> courses;
		std::vector<Grades *> grades;
		std::vector<Student *> studs;
		std::map<lab::xstring, lab::xstring> matchings;

	public:
		App();
		~App();

		template<typename T> bool import_data(const char *fpath);
		bool import_matchings(const char *fpath);
		
		const std::vector<Course *>& get_courses()	const;
		const std::vector<Grades *>& get_grades()	const;
		const std::vector<Student *>& get_studs()	const;
		const std::map<lab::xstring, lab::xstring>& get_matchings() const;

	private:
		template<typename T> void dealloc(std::vector<T *>& vec);
};

template<typename T>
bool App::import_data(const char *fpath)
{
	std::ifstream f;
	f.exceptions(std::ifstream::badbit);
	f.open(fpath);
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
		else if (std::is_same<T, Grades>::value)
		{
			lab::xstring AM, code, grade;
			lab::getline(f, AM, ';');
			lab::getline(f, code, ';');
			lab::getline(f, grade);
			if (f.eof()) break;
			grades.push_back(new Grades(AM, code, std::atof(grade.cstr())));
		
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

	}	
	f.close();
	return true;
}

template<typename T>
void App::dealloc(std::vector<T *>& vec)
{
	for (auto& v : vec)
		if (v != nullptr)
			delete v;
	vec.clear();
}

#endif /* APP_H */
