#include "student.h"

Student::Student(const char *AM, const std::string& name)
	:AM(convert_AM(AM)), name(name), semester(1), pcourses(0)
{
	nsc = 0;
	sc = nullptr;
}

Student::Student(const char *AM, const std::string& name, unsigned int semester)
	:AM(convert_AM(AM)), name(name), semester(semester), pcourses(0)
{
	nsc = 0;
	sc = nullptr;
}

Student::Student(const char *AM, const std::string& name, unsigned int semester,
			    unsigned int pcourses, const float *grades)
	:AM(convert_AM(AM)), name(name), semester(semester), pcourses(pcourses), grades(convert_PSG(grades))
{
	nsc = 0;
	sc = nullptr;
}

Student::Student(const Student& s)
	:name(s.name), semester(s.semester), pcourses(s.pcourses)
{
	int sl = strlen(s.AM);
	this->AM = new char[sl + 1];
	memcpy(AM, s.AM, sizeof(s.AM) + (sl+1));
	this->grades = new float[s.pcourses];
	memcpy(grades, s.grades, sizeof(float) * s.pcourses);

	if (s.nsc <= 0)
	{
		nsc = 0;
		sc = nullptr;
	}
	else
	{
		this->sc = new Course *[s.nsc];
		memcpy(sc, s.sc, sizeof(s.sc) * s.nsc);
	}
}

Student::~Student()
{
	if (this->AM != nullptr) delete[] this->AM;
	if (this->grades != nullptr) delete[] this->grades;
	if (this->sc != nullptr) delete[] this->sc;
}

void Student::operator+= (Course *c)
{
	Course **tmp = new Course *[nsc+1];
	if (sc != nullptr)
	{
		memcpy(tmp, sc, sizeof(Course *) * nsc);
		delete[] sc;
	}
	tmp[nsc] = c;
	sc = tmp;
	nsc++;
}

Student Student::operator= (const Student& s)
{
	if (this == &s) return *this;
	this->AM = convert_AM(s.AM);
	this->name = s.name;
	this->semester = s.semester;
	this->pcourses = s.pcourses;
	if (s.grades != nullptr) this->grades = convert_PSG(s.grades);
	if (s.sc != nullptr)
	{
		this->nsc = s.nsc;
		this->sc = s.sc;
	}
	return *this;
}

bool Student::operator== (const Student& s) const
{
	return this->semester == s.semester;
}

bool Student::operator!= (const Student& s) const
{
	return this->semester != s.semester;
}

bool Student::operator<	(const Student& s) const
{
	return this->semester < s.semester;
}

bool Student::operator<= (const Student& s) const
{
	return this->semester <= s.semester;
}

bool Student::operator> (const Student& s) const
{
	return this->semester > s.semester;
}

bool Student::operator>= (const Student& s) const
{
	return this->semester >= s.semester;
}

const char *Student::get_AM() const
{
	return this->AM;
}

const std::string& Student::get_name() const
{
	return this->name;
}

unsigned int Student::get_semester() const
{
	return this->semester;
}

unsigned int Student::get_pcourses() const
{
	return this->pcourses;
}

float *Student::get_grades() const
{
	return (this->pcourses > 0) ? this->grades : nullptr;
}

Course **Student::get_submitted_courses() const
{
	return this->sc;
}

unsigned int Student::get_num_submitted_courses() const
{
	return this->nsc;
}

void Student::set_AM(const char *AM)
{
	if (this->AM != nullptr) delete[] this->AM;
	this->AM = convert_AM(AM);
}

void Student::set_name(const std::string& name)
{
	this->name = name;
}

void Student::set_semester(unsigned int semester)
{
	this->semester = semester;
}

void Student::set_pcourses(unsigned int pcourses)
{
	this->pcourses = pcourses;
}

void Student::set_grades(float *grades)
{
	this->grades = convert_PSG(grades);
}

void Student::set_num_submitted_courses(unsigned nsc)
{
	this->nsc = nsc;
}

void Student::set_submitted_courses(Course **sc)
{
	if (sc != nullptr)
	{
		this->sc = new Course *[nsc];
		memcpy(this->sc, sc, sizeof(Course *) * nsc);
	}
}

char *Student::convert_AM(const char *AM)
{
	int len = strlen(AM);
	char *tmp = new char[len+1];
	memcpy(tmp, AM, len+1);
	return tmp;
}

float *Student::convert_PSG(const float *grades)
{
	if (pcourses > 0 && grades != nullptr)
	{
		float *tmp = new float[pcourses];
		memcpy(tmp, grades, sizeof(float) * pcourses);
		if (this->grades != nullptr) delete[] this->grades;
		return tmp;
	}
	else return nullptr;
}

void Student::add_grade(float grade)
{
	float *tmp = new float[pcourses+1];
	if (grades != nullptr)
	{
		memcpy(tmp, grades, sizeof(float) * pcourses);
		delete[] grades;
	}
	tmp[pcourses] = grade;
	grades = tmp;
	pcourses++;
}

void Student::detailed_print() const
{
	if (grades != nullptr)
	{
		for (unsigned int i = 0; i < pcourses; i++)
		{
			std::cout << "Course " << i+1 << ": ";
			std::cout << grades[i] << std::endl;		
		}
		std::cout << "Average grade: " << std::setprecision(2) << calc_average() << std::endl;
	}
}

float Student::calc_average() const
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
