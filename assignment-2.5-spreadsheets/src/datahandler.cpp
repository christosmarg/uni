#include "datahandler.h"

DataHandler::DataHandler() {}

DataHandler::~DataHandler()
{
	dealloc<Course>(courses);
	dealloc<Student>(studs);
	eqvs.clear();
}

bool
DataHandler::store_data()
{
	std::ifstream f;
	f.exceptions(std::ifstream::badbit);
	try
	{
		if (!valid_path(datapath))
			throw std::runtime_error(err_csv(datapath).cstr());
		f.open(datapath);
		if (f.is_open())
		{
			lab::xstring skip;
			lab::getline(f, skip);

			lab::xstring AM, code, grade;
			lab::getline(f, AM, ';');
			lab::getline(f, code, ';');
			lab::getline(f, grade);
			if (studs[AM] && courses[code])
				grd.insert(std::make_pair(courses[code],
							std::atof(grade.cstr())));

			while (f.good())
			{
				lab::xstring currAM = AM;
				// eats up first grade of each student
				while (currAM == AM)
				{
					lab::getline(f, AM, ';');
					lab::getline(f, code, ';');
					lab::getline(f, grade);
					if (f.eof()) break;
					if (!analyze(currAM, AM, code, grade)) break;
				}
			}
			for (const auto& d : data)
			{
				std::cout << d.first->get_AM() << std::endl << std::endl;
				for (const auto& da : d.second)
					std::cout << da.first->get_code() << " " << da.second << std::endl;
				std::cout << std::endl;
			}
		}
		f.close();	
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << err_read(datapath) << std::endl << e.what() << std::endl;
		return false;
	}
	return true;
}

bool
DataHandler::analyze(
		const lab::xstring& currAM,
		const lab::xstring& AM,
		const lab::xstring& code,
		const lab::xstring& grade)
{
	if (studs[AM] && courses[code])
	{
		if (currAM != AM)
		{
			data.insert(std::make_pair(studs[currAM], grd));
			grd.clear();
			return false;
		}
		grd.insert(std::make_pair(courses[code],
					std::atof(grade.cstr())));
	}
	else if (!studs[AM])
		errlog.write(ErrLog::ErrType::STUDENT_MISSING, AM);
	else if (!courses[code])
		errlog.write(ErrLog::ErrType::COURSE_MISSING, code);

	return true;
}

bool
DataHandler::make_report() const
{
	std::ofstream f;
	f.open(reppath);
	f.close();
	return true;
}

bool
DataHandler::valid_path(const char *fpath) const
{
	return (strstr(fpath, ".csv") != nullptr);
}

const lab::xstring 
DataHandler::err_csv(const char *fpath) const
{
	lab::xstring err = "Error. File must be of format \'.csv\'. ().";
	err.insert(fpath, 39);
	return err;
}

const lab::xstring
DataHandler::err_read(const char *fpath) const
{
	lab::xstring err = "Error reading file \'\'.";
	err.insert(fpath, 20);
	return err;
}

const lab::xstring
DataHandler::err_write(const char *fpath) const
{
	lab::xstring err = "Error writing to file \'\'.";
	err.insert(fpath, 23);
	return err;
}
