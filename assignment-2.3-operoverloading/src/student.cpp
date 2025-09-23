#include "student.h"

Student::Student(const char *AM, const std::string& name)
	:AM(convert_AM(AM)), name(name), semester(1), psubj(0) {}

Student::Student(const char *AM, const std::string& name, unsigned int semester)
	:AM(convert_AM(AM)), name(name), semester(semester), psubj(0) {}

Student::Student(const char *AM, const std::string& name, unsigned int semester,
			    unsigned int psubj, const float *grades)
	:AM(convert_AM(AM)), name(name), semester(semester), psubj(psubj), grades(convert_PSG(grades)) {}

Student::Student(const Student& s)
	:name(s.name), semester(s.semester), psubj(s.psubj)
{
	int sl = strlen(s.AM);
	this->AM = new char[sl + 1];
	std::copy(s.AM, s.AM+sl, AM);

	this->grades = new float[psubj];
	std::copy(s.grades, s.grades+psubj, grades);
}

Student::~Student()
{
	delete[] this->AM;
	delete[] this->grades;
	delete[] this->submittedSubjects;
}

void Student::operator+= (const std::string& s)
{
	std::string *tmp = new std::string[numSubmittedSubjects+1];
	std::copy(submittedSubjects, submittedSubjects+numSubmittedSubjects, tmp);
	tmp[numSubmittedSubjects] = s;
	delete[] submittedSubjects;
	submittedSubjects = new std::string[numSubmittedSubjects+1];
	std::copy(tmp, tmp+numSubmittedSubjects+1, submittedSubjects);
	numSubmittedSubjects++;
	delete[] tmp;
}

Student& Student::operator= (const Student& s)
{
	if (this == &s) return *this;
	this->AM = convert_AM(s.AM);
	this->name = s.name;
	this->semester = s.semester;
	this->psubj = s.psubj;
	if (s.grades != nullptr) this->grades = convert_PSG(s.grades);
	if (s.submittedSubjects != nullptr)
	{
		this->numSubmittedSubjects = s.numSubmittedSubjects;
		this->submittedSubjects = s.submittedSubjects;
	}
	return *this;
}

float *Student::get_grades() const
{
	float *ret = new float[psubj];
	std::copy(grades, grades+psubj, ret);
	return ret;
}

std::string *Student::get_submitted_subjects() const
{
	std::string *ret = new std::string[numSubmittedSubjects];
	std::copy(submittedSubjects, submittedSubjects+numSubmittedSubjects, ret);
	return ret;
}

void Student::set_submitted_subjects(std::string* submittedSubjects)
{
	this->submittedSubjects = new std::string[numSubmittedSubjects];
	std::copy(submittedSubjects, submittedSubjects+numSubmittedSubjects, this->submittedSubjects);
}

char *Student::convert_AM(const char *AM)
{
	int len = strlen(AM);
	this->AM = new char[len+1];
	std::copy(AM, AM+len, this->AM);
	return this->AM;
}

float *Student::convert_PSG(const float *grades)
{
	this->grades = new float[psubj];
	std::copy(grades, grades+psubj, this->grades);
	return this->grades;	
}

void Student::add_grade(float grade)
{
	float *tmp = new float[psubj+1];
	std::copy(grades, grades+psubj, tmp);
	tmp[psubj] = grade;
	delete[] grades;
	grades = new float[psubj+1];
	std::copy(tmp, tmp+psubj+1, grades);
	psubj++;
	delete[] tmp;
}

void Student::detailed_print() const
{
	for (unsigned int i = 0; i < psubj; i++)
	{
		std::cout << "Subject " << i+1 << ": ";
		std::cout << grades[i] << std::endl;		
	}
	std::cout << "Average grade: " << std::setprecision(2) << calc_average() << std::endl;
}

float Student::calc_average() const
{
	float sum = 0;
	for (unsigned int i = 0; i < psubj; i++)
		sum += grades[i];
	float average = sum / psubj;
	return average;
}
