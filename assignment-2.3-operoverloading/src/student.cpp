#include "student.h"

Student::Student(const char *AM, const std::string& name)
	:AM(convert_AM(AM)), name(name), semester(1), psubj(0)
{
	numSubmittedSubjects = 0;
	submittedSubjects = nullptr;
}

Student::Student(const char *AM, const std::string& name, unsigned int semester)
	:AM(convert_AM(AM)), name(name), semester(semester), psubj(0)
{
	numSubmittedSubjects = 0;
	submittedSubjects = nullptr;
}

Student::Student(const char *AM, const std::string& name, unsigned int semester,
			    unsigned int psubj, const float *grades)
	:AM(convert_AM(AM)), name(name), semester(semester), psubj(psubj), grades(convert_PSG(grades))
{
	numSubmittedSubjects = 0;
	submittedSubjects = nullptr;
}

Student::Student(const Student& s)
	:name(s.name), semester(s.semester), psubj(s.psubj)
{
	int sl = strlen(s.AM);
	this->AM = new char[sl + 1];
	memcpy(AM, s.AM, sizeof(s.AM) + (sl+1));
	this->grades = new float[s.psubj];
	memcpy(grades, s.grades, sizeof(s.grades) * s.psubj);

	if (s.numSubmittedSubjects <= 0)
	{
		numSubmittedSubjects = 0;
		submittedSubjects = nullptr;
	}
	else memcpy(submittedSubjects, s.submittedSubjects, sizeof(s.submittedSubjects) * s.numSubmittedSubjects);
}

Student::~Student()
{
	delete[] this->AM;
	delete[] this->grades;
	delete[] this->submittedSubjects;
}

Student& Student::operator+= (Subject* s)
{
	Subject **tmp = new Subject *[numSubmittedSubjects];
	memcpy(tmp, submittedSubjects, sizeof(Subject *) * numSubmittedSubjects);
	tmp[numSubmittedSubjects] = s;
	if (submittedSubjects != nullptr) delete[] submittedSubjects;
	submittedSubjects = tmp;
	numSubmittedSubjects++;
	return *this;
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

void Student::set_submitted_subjects(Subject **submittedSubjects)
{
	// handle 0 subj
	this->submittedSubjects = new Subject *[numSubmittedSubjects];
	memcpy(this->submittedSubjects, submittedSubjects, sizeof(Subject *) * numSubmittedSubjects);
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
	if (psubj > 0)
	{
		float *tmp = new float[psubj];
		memcpy(tmp, grades, sizeof(grades) * psubj);
		return tmp;
	}
	else return nullptr;
}

void Student::add_grade(float grade)
{
	float *tmp = new float[psubj+1];
	memcpy(tmp, grades, sizeof(grades) * psubj);
	tmp[psubj] = grade;
	if (grades != nullptr) delete[] grades;
	grades = tmp;
	psubj++;
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
