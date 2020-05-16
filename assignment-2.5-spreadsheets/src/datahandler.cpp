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

			std::map<lab::xstring, Student *>::const_iterator its = studs.find(AM);
			std::map<lab::xstring, Course *>::const_iterator itc = courses.find(code);
			if (its != studs.end() && itc != courses.end())
				grds.insert(std::make_pair(courses[code],
							std::atof(grade.cstr())));

			while (f.good())
			{
				lab::xstring currAM = AM;
				while (currAM == AM)
				{
					lab::getline(f, AM, ';');
					lab::getline(f, code, ';');
					lab::getline(f, grade);
					if (f.eof()) break;
					if (!analyze(currAM, AM, code, grade)) break;
				}
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
		lab::xstring& AM,
		lab::xstring& code,
		lab::xstring& grade)
{
	std::map<lab::xstring, Student *>::const_iterator its = studs.find(AM);
	std::map<lab::xstring, Course *>::const_iterator itc = courses.find(code);
	if (its != studs.end() && itc != courses.end())
	{
		if (currAM != AM)
		{
			data.insert(std::make_pair(studs[currAM], grds));
			grds.clear();
			grds.insert(std::make_pair(courses[code],
						std::atof(grade.cstr())));
			return false;
		}
		grds.insert(std::make_pair(courses[code],
					std::atof(grade.cstr())));
	}
	else if (its == studs.end())
		errlog.write(ErrLog::ErrType::STUDENT_MISSING, AM);
	else if (itc == courses.end())
		errlog.write(ErrLog::ErrType::COURSE_MISSING, code);

	if (its != studs.end() && itc != courses.end())
	{
		missing(AM, code);	
		diffgrds(AM, code, grade);
	}

	return true;
}

void
DataHandler::missing(lab::xstring& AM, lab::xstring& code)
{
	if (code.front() == 'P')
	{
		std::map<lab::xstring, lab::xstring>::const_iterator it = eqvs.find(code);
		if (it != eqvs.end())
		{
			bool found = false;
			for (const auto& grd : grds)
				if (grd.first->get_code() == eqvs[code])
					found = true;
			if (!found) missgrds.push_back(AM + ";" + code);
		}
	}
}

void
DataHandler::diffgrds(lab::xstring& AM, lab::xstring& code, lab::xstring& grade)
{
	float g = std::atof(grade.cstr());
	for (const auto& grd : grds)
		if (code == grd.first->get_code() && grd.second != g)
			errlog.write(ErrLog::ErrType::DIFFERENT_GRADES,
					lab::xstring(AM + " in " + code + ": " +
						lab::to_xstr<float>("%.1f", grd.second) + " | " +
						lab::to_xstr<float>("%.1f", g))
					);
}


bool
DataHandler::make_report() const
{
	std::ofstream f;
	f.open(reppath);
	f << "Student;Course" << std::endl;
	for (const auto& missgrd : missgrds)
		f << missgrd << std::endl;
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
