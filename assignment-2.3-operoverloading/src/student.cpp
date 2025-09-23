#include "student.h"

Student::Student(const char *AM, const std::string& name)
	:AM(convert_AM(AM)), name(name), semester(1), psubj(0)
{
	nssubj = 0;
	ssubj = nullptr;
}

Student::Student(const char *AM, const std::string& name, unsigned int semester)
	:AM(convert_AM(AM)), name(name), semester(semester), psubj(0)
{
	nssubj = 0;
	ssubj = nullptr;
}

Student::Student(const char *AM, const std::string& name, unsigned int semester,
			    unsigned int psubj, const float *grades)
	:AM(convert_AM(AM)), name(name), semester(semester), psubj(psubj), grades(convert_PSG(grades))
{
	nssubj = 0;
	ssubj = nullptr;
}

Student::Student(const Student& s)
	:name(s.name), semester(s.semester), psubj(s.psubj)
{
	int sl = strlen(s.AM);
	this->AM = new char[sl + 1];
	memcpy(AM, s.AM, sizeof(s.AM) + (sl+1));
	this->grades = new float[s.psubj];
	memcpy(grades, s.grades, sizeof(float) * s.psubj);

	if (s.nssubj <= 0)
	{
		nssubj = 0;
		ssubj = nullptr;
	}
	else
	{
		this->ssubj = new Subject *[s.nssubj];
		memcpy(ssubj, s.ssubj, sizeof(s.ssubj) * s.nssubj);
	}
}

Student::~Student()
{
	if (this->AM != nullptr) delete[] this->AM;
	if (this->grades != nullptr) delete[] this->grades;
	if (this->ssubj != nullptr) delete[] this->ssubj;
}

void Student::operator+= (Subject *s)
{
	Subject **tmp = new Subject *[nssubj+1];
	if (ssubj != nullptr)
	{
		memcpy(tmp, ssubj, sizeof(Subject *) * nssubj);
		delete[] ssubj;
	}
	tmp[nssubj] = s;
	ssubj = tmp;
	nssubj++;
}

Student Student::operator= (const Student& s)
{
	if (this == &s) return *this;
	this->AM = convert_AM(s.AM);
	this->name = s.name;
	this->semester = s.semester;
	this->psubj = s.psubj;
	if (s.grades != nullptr) this->grades = convert_PSG(s.grades);
	if (s.ssubj != nullptr)
	{
		this->nssubj = s.nssubj;
		this->ssubj = s.ssubj;
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

unsigned int Student::get_psubj() const
{
	return this->psubj;
}

float *Student::get_grades() const
{
	return (this->psubj > 0) ? this->grades : nullptr;
}

Subject **Student::get_submitted_subjects() const
{
	return this->ssubj;
}

unsigned int Student::get_num_submitted_subjects() const
{
	return this->nssubj;
}

void Student::set_AM(const char *AM)
{
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

void Student::set_psubj(unsigned int psubj)
{
	this->psubj = psubj;
}

void Student::set_grades(float *grades)
{
	this->grades = convert_PSG(grades);
}

void Student::set_num_submitted_subjects(unsigned nssubj)
{
	this->nssubj = nssubj;
}

void Student::set_submitted_subjects(Subject **ssubj)
{
	if (ssubj != nullptr)
	{
		this->ssubj = new Subject *[nssubj];
		memcpy(this->ssubj, ssubj, sizeof(Subject *) * nssubj);
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
	if (psubj > 0)
	{
		float *tmp = new float[psubj];
		memcpy(tmp, grades, sizeof(float) * psubj);
		return tmp;
	}
	else return nullptr;
}

void Student::add_grade(float grade)
{
	float *tmp = new float[psubj+1];
	if (grades != nullptr)
	{
		memcpy(tmp, grades, sizeof(float) * psubj);
		delete[] grades;
	}
	tmp[psubj] = grade;
	grades = tmp;
	psubj++;
}

void Student::detailed_print() const
{
	if (grades != nullptr)
	{
		for (unsigned int i = 0; i < psubj; i++)
		{
			std::cout << "Subject " << i+1 << ": ";
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
		for (unsigned int i = 0; i < psubj; i++)
			sum += grades[i];
		float average = sum / psubj;
		return average;
	}
	else return 0.0f;
}
