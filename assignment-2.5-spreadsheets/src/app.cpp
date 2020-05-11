#include "app.h"

App::App() {}

App::~App()
{
	dealloc<Course>(courses);
	dealloc<Grade>(grades);
	dealloc<Student>(studs);	
}

const std::vector<Course *>&
App::get_courses() const
{
	return courses;
}

const std::vector<Grade *>&
App::get_grades() const
{
	return grades;
}

const std::vector<Student *>&
App::get_studs() const
{
	return studs;
}

const equivalencies&
App::get_eqvs() const
{
	return eqvs;
}

bool
App::valid_path(const char *fpath)
{
	return (strstr(fpath, ".csv") != nullptr);
}

const lab::xstring 
App::err_csv(const char *fpath)
{
	lab::xstring err = "Error. File must be of format \'.csv\'. ().";
	err.insert(fpath, 39);
	return err;
}

const lab::xstring
App::err_read(const char *fpath)
{
	lab::xstring err = "Error reading file \'\'.";
	err.insert(fpath, 20);
	return err;
}

const lab::xstring
App::err_write(const char *fpath)
{
	lab::xstring err = "Error writing to file \'\'.";
	err.insert(fpath, 23);
	return err;
}
