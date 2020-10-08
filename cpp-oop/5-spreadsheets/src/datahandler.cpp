#include "datahandler.hpp"

DataHandler::DataHandler()
    :misscount(0), errcount(0) {}

DataHandler::~DataHandler()
{
    dealloc<Course>(courses);
    dealloc<Student>(studs);
    if (!grds.empty()) grds.clear();
    if (!data.empty()) data.clear();
    if (!eqvs.empty()) eqvs.clear();
    if (!errs.empty()) errs.clear();
    if (!missing.empty()) missing.clear();
}

void
DataHandler::load_grades()
{
    std::ifstream f;
    f.exceptions(std::ifstream::badbit);
    try
    {
        f.open(datapath);
        if (f.is_open())
        {
            std::printf("Importing data from \'%s\'\n\n", datapath);
            std::printf("Making data structures and analyzing data.\n");
            lab::xstring skip;
            lab::getline(f, skip);

            lab::xstring id, code, grade;
            lab::getline(f, id, ';');
            lab::getline(f, code, ';');
            lab::getline(f, grade);

            std::map<lab::xstring, Student *>::const_iterator its = studs.find(id);
            std::map<lab::xstring, Course *>::const_iterator itc = courses.find(code);
            if (its != studs.end() && itc != courses.end())
                grds.insert(std::make_pair(courses[code], std::atof(grade.cstr())));

            while (f.good())
            {
                lab::xstring currid = id;
                while (currid == id)
                {
                    lab::getline(f, id, ';');
                    lab::getline(f, code, ';');
                    lab::getline(f, grade);
                    if (f.eof()) break;
                    analyze(currid, id, code, std::atof(grade.cstr()));
                }
            }
        }
        f.close();  
    }
    catch (const std::ifstream::failure& e)
    {
        errlog.write(ErrLog::ErrType::RUNTIME_ERR, err_read(datapath));
        throw std::runtime_error(err_read(datapath).cstr());
    }
}

void
DataHandler::analyze(
        const lab::xstring& currid,
        lab::xstring& id,
        lab::xstring& code,
        float grade)
{
    std::map<lab::xstring, Student *>::const_iterator its = studs.find(id);
    std::map<lab::xstring, Course *>::const_iterator itc = courses.find(code);
    if (its != studs.end() && itc != courses.end())
    {
        if (currid != id)
        {
            data.insert(std::make_pair(studs[currid], grds));
            grds.clear();
            grds.insert(std::make_pair(courses[code], grade));
            return;
        }
        grds.insert(std::make_pair(courses[code], grade));
    }
    else if (its == studs.end() && 
            std::find(errs.begin(), errs.end(), id) == errs.end())
    {
            errs.push_back(id);
            errlog.write(ErrLog::ErrType::STUDENT_MISSING, id);
            errcount++;
    }
    else if (itc == courses.end() &&
            std::find(errs.begin(), errs.end(), code) == errs.end())
    {
            errs.push_back(code);
            errlog.write(ErrLog::ErrType::COURSE_MISSING, code);
            errcount++;
    }

    if (its != studs.end() && itc != courses.end())
    {
        miss(id, code, grade);  
        diffr(id, code, grade);
    }
}

void
DataHandler::miss(lab::xstring id, lab::xstring code, float grade)
{
    if (courses[code]->four_year)
    {
        std::map<lab::xstring, lab::xstring>::const_iterator it = eqvs.find(code);
        if (it != eqvs.end())
        {
            bool found = false;
            for (const auto& grd : grds)
                if (grd.first->code == eqvs[code])
                    found = true;
            if (!found)
            {
                missing.push_back(id + ";" +
                        studs[id]->lname + ";" +
                        studs[id]->fname + ";" +
                        courses[eqvs[code]]->code + ";" +
                        courses[eqvs[code]]->name + ";" +
                        code + ";" +
                        courses[code]->name + ";" +
                        lab::to_xstr<float>("%.1f", grade));
                misscount++;
            }
        }
    }
}

void
DataHandler::diffr(lab::xstring id, lab::xstring code, float grade)
{
    std::map<Course *, float>::const_iterator it = grds.find(courses[code]);
    if (it != grds.end() && it->second != grade)
    {
        errlog.write(ErrLog::ErrType::DIFFERENT_GRADES,
                lab::xstring(id + " in " + code + ": " +
                    lab::to_xstr<float>("%.1f", it->second) + " | " +
                    lab::to_xstr<float>("%.1f", grade)));
        errcount++;
    }
}

void
DataHandler::make_report() const
{
    std::ofstream f;
    f.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try
    {
        f.open(reppath);
        if (f.is_open())
        {
            std::printf("Making report.\n");
            f << "ID;Last name;First name;New course code;New course name;" <<
                 "Old course code;Old course name;Grade" << std::endl;
            for (const auto& m : missing) f << m << std::endl;
            f.close();
        }
    }
    catch (const std::ofstream::failure& e)
    {
        errlog.write(ErrLog::ErrType::RUNTIME_ERR, err_write(reppath));
    }
}


void
DataHandler::summary() const
{
    int datacount = 0;
    for (const auto& dat : data)
        datacount += dat.second.size();

    std::printf("\nStudents: %ld\n", studs.size());
    std::printf("Courses: %ld\n", courses.size());
    std::printf("Equivalences: %ld\n", eqvs.size());
    std::printf("Total grades stored: %d\n", datacount);
    std::printf("Grades missing: %d\n", misscount); 
    std::printf("Errors: %d\n", errcount);
    std::printf("\nThank you :)\n");
}

const lab::xstring
DataHandler::err_read(const char *fpath) const
{
    return lab::xstring("Error reading file \'\'.").insert(fpath, 20);
}

const lab::xstring
DataHandler::err_write(const char *fpath) const
{
    return lab::xstring("Error writing to file \'\'.").insert(fpath, 23);
}
