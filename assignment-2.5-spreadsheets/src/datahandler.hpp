#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "course.hpp"
#include "errlog.hpp"
#include "student.hpp"
#include "xstring.hpp"

using equivalencies = std::map<lab::xstring, lab::xstring>;

class DataHandler 
{
    private:
        static constexpr const char *datapath = "res/grades.csv";
        static constexpr const char *reppath = "res/report.csv";
        std::map<lab::xstring, Course *> courses;
        std::map<lab::xstring, Student *> studs;
        std::map<Course *, float> grds;
        std::map<Student *, std::map<Course *, float>> data;
        std::vector<lab::xstring> errs;
        std::vector<lab::xstring> missing;
        equivalencies eqvs;
        ErrLog errlog;
        int misscount, errcount;

    public:
        DataHandler();
        ~DataHandler();

        template<typename T> void import_data(const char *fpath);
        bool load_grades();
        void make_report() const;
        void summary() const;
        
    private:
        bool analyze(
                const lab::xstring& currid,
                lab::xstring& id,
                lab::xstring& code,
                float grade);
        void miss(lab::xstring id, lab::xstring code, float grade);
        void diffr(lab::xstring id, lab::xstring code, float grade);
        const lab::xstring err_read (const char *fpath) const;
        const lab::xstring err_write(const char *fpath) const;
        template<typename T> void dealloc(std::map<lab::xstring, T *>& vec);
};

template<typename T> void
DataHandler::import_data(const char *fpath)
{
    std::ifstream f;
    f.exceptions(std::ifstream::badbit);
    try
    {
        f.open(fpath);
        if (f.is_open())
        {
            std::printf("Importing data from \'%s\'\n", fpath);
            lab::xstring skip;
            lab::getline(f, skip);
            while (f.good())
            {
                if constexpr (std::is_same_v<T, Course>)
                {
                    lab::xstring code, name;
                    lab::getline(f, code, ';');
                    lab::getline(f, name);
                    if (f.eof()) break;
                    courses.insert(std::make_pair(code, new Course(code, name)));
                }
                else if constexpr (std::is_same_v<T, Student>)
                {
                    lab::xstring id, lname, fname;
                    lab::getline(f, id, ';');
                    lab::getline(f, lname, ';');
                    lab::getline(f, fname);
                    if (f.eof()) break;
                    studs.insert(std::make_pair(id, new Student(id, lname, fname)));
                }
                else if constexpr (std::is_same_v<T, equivalencies>)
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
        errlog.write(ErrLog::ErrType::RUNTIME_ERR, err_read(fpath));
    }
}

template<typename T> void
DataHandler::dealloc(std::map<lab::xstring, T *>& vec)
{
    if (!vec.empty())
    {
        for (auto&& v : vec)
            if (v.second != nullptr)
                delete v.second;
        vec.clear();
    }
}

#endif /* DATA_HANDLER_HPP */
