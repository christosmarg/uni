#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "course.h"
#include "errlog.h"
#include "student.h"
#include "xstring.h"

typedef std::map<lab::xstring, lab::xstring> equivalencies;

class DataHandler 
{
	private:
		const char *datapath = "res/grades.csv";
		const char *reppath = "res/report.csv";
		std::map<lab::xstring, Course *> courses;
		std::map<lab::xstring, Student *> studs;
		std::map<Course *, float> grds;
		std::map<Student *, std::map<Course *, float>> data;
		std::vector<lab::xstring> missing;
		equivalencies eqvs;
		ErrLog errlog;
		int misscount, errcount;

	public:
		DataHandler();
		~DataHandler();

		template<typename T> bool import_data(const char *fpath);
		bool store_data();
		bool make_report() const;
		void summary() const;
		
	private:
		bool analyze(
				const lab::xstring& currAM,
				lab::xstring& AM,
				lab::xstring& code,
				float grade);
		void miss(lab::xstring AM, lab::xstring code, float grade);
		void diffr(lab::xstring AM, lab::xstring code, float grade);
		bool valid_path(const char *fpath) const;
		const lab::xstring err_csv	(const char *fpath)	const;
		const lab::xstring err_read	(const char *fpath)	const;
		const lab::xstring err_write(const char *fpath) const;
		template<typename T> void dealloc(std::map<lab::xstring, T *>& vec);
};

template<typename T> bool
DataHandler::import_data(const char *fpath)
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
			std::cout << "Importing data from \'" << fpath << "\'." << std::endl;
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
					lab::xstring oldcurr, newcurr;
					lab::getline(f, oldcurr, ';');
					lab::getline(f, newcurr);
					if (f.eof()) break;
					eqvs.insert(std::make_pair(oldcurr, newcurr));
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
DataHandler::dealloc(std::map<lab::xstring, T *>& vec)
{
	if (!vec.empty())
	{
		for (auto&& v : vec)
		{
			if (v.second != nullptr)
			{
				delete v.second;
				v.second = nullptr;	
			}
		}
		vec.clear();
	}
}

#endif /* DATA_HANDLER_H */
