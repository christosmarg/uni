#include "app.h"

std::ostream& operator<< (std::ostream& stream, const App& app);

int
main(int argc, char **argv)
{
	App app;
	if (!app.import_data<Course>("res/courses.csv")) return -1;
	if (!app.import_data<Grades>("res/grades.csv")) return -1;
	if (!app.import_data<Student>("res/students.csv")) return -1;
	if (!app.import_matchings("res/matchings.csv")) return -1;
	//std::cout << app << std::endl;
	
	std::map<lab::xstring, lab::xstring> a = app.get_matchings();
	std::map<lab::xstring, lab::xstring>::const_iterator it;
	for (it = a.begin(); it != a.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	
	return 0;
}

std::ostream&
operator<< (std::ostream& stream, const App& app)
{
	return stream;	
}
