#include "app.h"

std::ostream& operator<< (std::ostream& stream, const App& app);

int
main(int argc, char **argv)
{
	App app;
	if (!app.import_data<Course>("res/courses.csv")) return -1;
	if (!app.import_data<Grade>("res/grades.csv")) return -1;
	if (!app.import_data<Student>("res/students.csv")) return -1;
	if (!app.import_data<equivalencies>("res/equivalencies.csv")) return -1;
	
	equivalencies a = app.get_eqvs();
	equivalencies::const_iterator it;
	for (it = a.begin(); it != a.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;

	return 0;
}

std::ostream&
operator<< (std::ostream& stream, const App& app)
{
	return stream;	
}
