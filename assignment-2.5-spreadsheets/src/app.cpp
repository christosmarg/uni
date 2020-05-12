#include "app.h"

App::App() {}

App::~App()
{
	dealloc<Course>(courses);
	dealloc<Student>(studs);
	eqvs.clear();
}

void
App::store_data()
{
	for (auto& stud : studs)
		std::cout << stud.first << std::endl;
}

void
App::analyze()
{
	std::ifstream f;
	const char *fpath = "res/grades.csv";
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
				lab::xstring AM, code, grade;
				lab::getline(f, AM, ';');
				lab::getline(f, code, ';');
				lab::getline(f, grade);
			}
		}
		f.close();	
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << err_read(fpath) << std::endl << e.what() << std::endl;
	}
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
