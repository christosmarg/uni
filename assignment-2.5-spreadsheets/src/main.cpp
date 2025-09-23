#include "datahandler.h"

int
main(int argc, char **argv)
{
	DataHandler dh;
	if (!dh.import_data<Course>("res/courses.csv")) return -1;
	if (!dh.import_data<Student>("res/students.csv")) return -1;
	if (!dh.import_data<equivalencies>("res/equivalencies.csv")) return -1;
	if (!dh.store_data()) return -1;
	if (!dh.make_report()) return -1;
	dh.summary();

	return 0;
}
