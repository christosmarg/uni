#include "student.h"

Student::Student(const char *id, const std::string& name)
    :id(convid(id)), name(name), semester(1), pcourses(0),
    sc(nullptr), nsc(0) {}

Student::Student(const char *id, const std::string& name,
        const unsigned int semester)
    :id(convid(id)), name(name), semester(semester), pcourses(0),
    sc(nullptr), nsc(0) {}

Student::Student(const char *id, const std::string& name,
        const unsigned int semester,
        const unsigned int pcourses, const float *grades)
    :id(convid(id)), name(name), semester(semester), pcourses(pcourses),
    grades(convpsg(grades)), sc(nullptr), nsc(0) {}

Student::Student(const Student& s)
    :name(s.name), semester(s.semester), pcourses(s.pcourses)
{
    int sl = std::strlen(s.id);
    this->id = new char[sl + 1];
    std::memcpy(id, s.id, sizeof(s.id) + (sl+1));
    this->grades = new float[s.pcourses];
    std::memcpy(grades, s.grades, sizeof(float) * s.pcourses);

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
    if (this->id != nullptr)
    {
        delete[] this->id;
        this->id = nullptr; 
    }
    if (this->grades != nullptr)
    {
        delete[] this->grades;
        this->grades = nullptr; 
    }       
    if (this->sc != nullptr)
    {
        delete[] this->sc;
        this->sc = nullptr;
    }
}

void
Student::operator+= (Course *c)
{
    Course **tmp = new Course *[nsc+1];
    if (sc != nullptr)
    {
        std::memcpy(tmp, sc, sizeof(Course *) * nsc);
        delete[] sc;
    }
    tmp[nsc] = c;
    sc = tmp;
    nsc++;
}

Student
Student::operator= (const Student& s)
{
    if (this == &s) return *this;
    this->id = convid(s.id);
    this->name = s.name;
    this->semester = s.semester;
    this->pcourses = s.pcourses;
    if (s.grades != nullptr) this->grades = convpsg(s.grades);
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
    return this->name;
}

void
Student::set_id(const char *id)
{
    if (this->id != nullptr) delete[] this->id;
    this->id = convid(id);
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
    this->grades = convpsg(grades);
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

char *
Student::convid(const char *id)
{
    int len = std::strlen(id);
    char *tmp = new char[len+1];
    std::memcpy(tmp, id, len+1);
    return tmp;
}

float *
Student::convpsg(const float *grades)
{
    if (pcourses > 0 && grades != nullptr)
    {
        float *tmp = new float[pcourses];
        std::memcpy(tmp, grades, sizeof(float) * pcourses);
        if (this->grades != nullptr) delete[] this->grades;
        return tmp;
    }
    else return nullptr;
}

void
Student::add_grade(const float grade)
{
    float *tmp = new float[pcourses+1];
    if (grades != nullptr)
    {
        std::memcpy(tmp, grades, sizeof(float) * pcourses);
        delete[] grades;
    }
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
