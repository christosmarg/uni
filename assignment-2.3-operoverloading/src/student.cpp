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
