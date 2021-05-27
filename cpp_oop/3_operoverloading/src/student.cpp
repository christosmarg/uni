#include "student.hpp"

Student::Student(const char *id, const std::string& name)
    :id(conv<char>(id, len(id))), name(name), semester(1),
    pcourses(0), sc(nullptr), nsc(0) {}

Student::Student(const char *id, const std::string& name,
        const unsigned int semester)
    :id(conv<char>(id, len(id))), name(name), semester(semester),
    pcourses(0), sc(nullptr), nsc(0) {}

Student::Student(const char *id, const std::string& name,
        const unsigned int semester,
        const unsigned int pcourses, const float *grades)
    :id(conv<char>(id, len(id))), name(name), semester(semester),
    pcourses(pcourses), grades(conv<float>(grades, pcourses)),
    sc(nullptr), nsc(0) {}

Student::Student(const Student& s)
    :name(s.name), semester(s.semester), pcourses(s.pcourses)
{
    this->id = conv<char>(s.id, len(s.id));
    this->grades = conv<float>(s.grades, s.pcourses);
    if (s.nsc <= 0)
    {
        nsc = 0;
        sc = nullptr;
    }
    else
    {
        this->sc = new Course *[s.nsc];
        std::memcpy(sc, s.sc, sizeof(s.sc) * s.nsc);
    }
}

Student::~Student()
{
    if (this->id != nullptr) delete[] this->id;
    if (this->grades != nullptr) delete[] this->grades;
    if (this->sc != nullptr) delete[] this->sc;
}

void
Student::operator+= (Course *c)
{
    Course **tmp = resize<Course *>(sc, nsc);
    tmp[nsc] = c;
    sc = tmp;
    nsc++;
}

Student
Student::operator= (const Student& s)
{
    if (this == &s) return *this;
    this->id = conv<char>(s.id, len(s.id)); 
    this->name = s.name;
    this->semester = s.semester;
    this->pcourses = s.pcourses;
    if (s.grades != nullptr)
        this->grades = conv<float>(s.grades, s.pcourses);
    if (s.sc != nullptr)
    {
        this->nsc = s.nsc;
        this->sc = s.sc;
    }
    return *this;
}

const std::string&
Student::get_name() const
{
    return name;
}

void
Student::set_id(const char *id)
{
    if (this->id != nullptr) delete[] this->id;
    this->id = conv<char>(id, len(id));
}

void
Student::set_name(const std::string& name)
{
    this->name = name;
}

void
Student::set_semester(const unsigned int semester)
{
    this->semester = semester;
}

void
Student::set_pcourses(const unsigned int pcourses)
{
    this->pcourses = pcourses;
}

void
Student::set_grades(const float *grades)
{
    this->grades = conv<float>(grades, pcourses);
}

void
Student::set_num_submitted_courses(const unsigned nsc)
{
    this->nsc = nsc;
}

void
Student::set_submitted_courses(Course **sc)
{
    if (sc != nullptr)
    {
        if (this->sc != nullptr) delete[] this->sc;
        this->sc = new Course *[nsc];
        std::memcpy(this->sc, sc, sizeof(Course *) * nsc);
    }
}

void
Student::add_grade(const float grade)
{
    float *tmp = resize<float>(grades, pcourses);
    tmp[pcourses] = grade;
    grades = tmp;
    pcourses++;
}

void
Student::detailed_print() const
{
    if (grades != nullptr)
    {
        for (unsigned int i = 0; i < pcourses; i++)
        {
            std::cout << "Course " << i+1 << ": ";
            std::cout << grades[i] << std::endl;        
        }
        std::cout << "Average grade: " << std::setprecision(2) << avg() << std::endl;
    }
}

float
Student::avg() const
{
    if (grades != nullptr)
    {
        float sum = 0;
        for (unsigned int i = 0; i < pcourses; i++)
            sum += grades[i];
        float average = sum / pcourses;
        return average;
    }
    else return 0.0f;
}
