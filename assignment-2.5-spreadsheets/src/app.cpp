#include "app.h"

App::App() {}

App::~App()
{
	dealloc<Course>(courses);
	dealloc<Grades>(grades);
	dealloc<Student>(studs);	
}

bool App::import_matchings(const char *fpath)
{
	std::ifstream f;
	f.open(fpath);
	// exceptions
	while (f.good())
	{
		lab::xstring newcurr, oldcurr;
		lab::getline(f, newcurr, ';');
		lab::getline(f, oldcurr);
		if (f.eof()) break;
		matchings.emplace_back(newcurr, oldcurr);
	}
	f.close();
	return true;
}

const std::vector<Course *>& App::get_courses() const
{
	return courses;
}

const std::vector<Grades *>& App::get_grades() const
{
	return grades;
}

const std::vector<Student *>& App::get_studs() const
{
	return studs;
}
