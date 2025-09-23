#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <string.h>

class Student
{
	private:
		char *AM;
		std::string name;
		unsigned int semester;
		unsigned int pcourses;
		float *grades;
		int size;

	public:
		Student(const char *AM, const std::string& name);
		Student(const char *AM, const std::string& name, unsigned int semester);
		Student(const char *AM, const std::string& name, unsigned int semester,
				unsigned int pcourses, const float *grades);
		Student(const Student& s);
		~Student();

		const char *get_AM() const;
		const std::string& get_name() const;
		unsigned int get_semester() const;
		unsigned int get_pcourses() const;
		float *get_grades() const;

		void set_AM(const char *AM);
		void set_name(const std::string& name);
		void set_semester(unsigned int semester);
		void set_pcourses(unsigned int pcourses);
		void set_grades(float *grades);

		void add_grade(float grade);
		void detailed_print() const;

	private:
		char *convert_AM(const char *AM);
		float *convert_PSG(const float *grades);
		float calc_average() const;
};

Student::Student(const char *AM, const std::string& name)
	:AM(convert_AM(AM)), name(name), semester(1), pcourses(0), grades(nullptr) {}

Student::Student(const char *AM, const std::string& name, unsigned int semester)
	:AM(convert_AM(AM)), name(name), semester(semester), pcourses(0), grades(nullptr) {}

Student::Student(const char *AM, const std::string& name, unsigned int semester,
		unsigned int pcourses, const float *grades)
	:AM(convert_AM(AM)), name(name), semester(semester), pcourses(pcourses), grades(convert_PSG(grades)) {}

Student::Student(const Student& s)
	:name(s.name), semester(s.semester), pcourses(s.pcourses)
{
	int sl = strlen(s.AM);
	AM = new char[sl + 1];
	memcpy(AM, s.AM, sizeof(s.AM) + (sl+1));
	this->grades = new float[s.pcourses];
	memcpy(grades, s.grades, sizeof(float) * s.pcourses);
}

Student::~Student()
{
	if (this->AM != nullptr) delete[] this->AM;
	if (this->AM != nullptr) delete[] this->grades;
}

const char *
Student::get_AM() const
{
	return this->AM;
}

const std::string&
Student::get_name() const
{
	return this->name;
}

unsigned int
Student::get_semester() const
{
	return this->semester;
}

unsigned int
Student::get_pcourses() const
{
	return this->pcourses;
}

float *
Student::get_grades() const
{
	return this->grades;
}

void
Student::set_AM(const char *AM)
{
	if (this->AM != nullptr) delete[] this->AM;
	this->AM = convert_AM(AM);
}

void
Student::set_name(const std::string& name)
{
	this->name = name;
}

void
Student::set_semester(unsigned int semester)
{
	this->semester = semester;
}

void
Student::set_pcourses(unsigned int pcourses)
{
	this->pcourses = pcourses;
}

void
Student::set_grades(float *grades)
{
	this->grades = convert_PSG(grades);
}

char *
Student::convert_AM(const char *AM)
{
	int len = strlen(AM);
	char *tmp = new char[len+1];
	memcpy(tmp, AM, len+1);
	return tmp;
}

float *
Student::convert_PSG(const float *grades)
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

void
Student::add_grade(float grade)
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

void
Student::detailed_print() const
{
	if (grades != nullptr)
	{
		for (unsigned int i = 0; i < pcourses; i++)
		{
			std::cout << "Subject " << i+1 << ": ";
			std::cout << grades[i] << std::endl;		
		}
		std::cout << "Average grade: " << std::setprecision(2) << calc_average() << std::endl;
	}
}

float
Student::calc_average() const
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

std::ostream& operator<< (std::ostream& stream, const Student& s);
static void cont(void);
static void constructor1(const Student& s1);
static void ostream_overload(const Student& s1);
static void constructor2(const Student& s2);
static void copy_constructor(const Student& copystud);
static void constructor3(const Student& s3);
static void detprint (const Student& s3);
static void setters(Student& s3);
static void addgrd(Student& s3);

int
main(int argc, char **argv)
{
	std::string n1 = "Name Surname";
	std::string n2 = "Name Surnamington";
	std::string n3 = "Name Surnaming";

	Student *s1 = new Student("12345678", n1);
	system("clear || cls");
	constructor1(*s1); cont();
	ostream_overload(*s1); cont();
	delete s1;
	
	Student *s2 = new Student("92345678", n2, 2);
	constructor2(*s2); cont();

	Student *copystud = new Student(*s2);
	copy_constructor(*copystud); cont();
	delete copystud;
	delete s2;

	float *grd = new float[4]{9.4f, 8.4f, 5.5f, 6.3f};
	Student *s3 = new Student("72345678", n3, 2, 4, grd);
	delete[] grd;
	constructor3(*s3); cont();
	detprint(*s3); cont();
	setters(*s3);
	addgrd(*s3); cont();
	delete s3;

	return 0;
}

std::ostream&
operator<< (std::ostream& stream, const Student& s)
{
	return stream <<
		"AM: " << s.get_AM() << std::endl <<
		"Name: " << s.get_name() << std::endl <<
		"Semester: " << s.get_semester() << std::endl;
}

static void
cont(void)
{
	std::cout << std::endl;
	std::cout << "Press <ENTER> to continue. . .";
	if (std::cin.get()) system("clear || cls");
}

static void
constructor1(const Student& s1)
{
	std::cout << "Constructor for s1 (AM, Name)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s1.get_AM() << std::endl;
	std::cout << "Name: " << s1.get_name() << std::endl;
	std::cout << "Semester (default value): " << s1.get_semester() << std::endl;
	std::cout << "Courses passed (default value): " << s1.get_pcourses() << std::endl;
}

static void
ostream_overload(const Student& s1)
{
	std::cout << "std::ostream overload" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << s1 << std::endl;
}

static void
constructor2(const Student& s2)
{
	std::cout << "Constructor for s2 (AM, Name, Semester)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s2.get_AM() << std::endl;
	std::cout << "Name: " << s2.get_name() << std::endl;
	std::cout << "Semester: " << s2.get_semester() << std::endl;
	std::cout << "Courses passed (default value): " << s2.get_pcourses() << std::endl;
}

static void
copy_constructor(const Student& copystud)
{
	std::cout << "Copy Constructor using copystud object as a copy of s2" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << copystud.get_AM() << std::endl;
	std::cout << "Name: " << copystud.get_name() << std::endl;
	std::cout << "Semester: " << copystud.get_semester() << std::endl;
	std::cout << "Courses passed (default value): " << copystud.get_pcourses() << std::endl;
}

static void
constructor3(const Student& s3)
{
	std::cout << "Constructor for s3 (AM, Name, Semester, Courses passed, Grades)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s3.get_AM() << std::endl;
	std::cout << "Name: " << s3.get_name() << std::endl;
	std::cout << "Semester: " << s3.get_semester() << std::endl;
	std::cout << "Courses passed: " << s3.get_pcourses() << std::endl;

	float *gr = s3.get_grades();
	if (gr != nullptr)
	{
		std::cout << "Grades: ";
		for (unsigned int i = 0; i < s3.get_pcourses(); i++)
		{
			if (i != s3.get_pcourses()-1) std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl;
		}
	}
}

static void
detprint (const Student& s3)
{
	std::cout << "Detailed print of s3's grades" << std::endl;
	std::cout << "----------------------------" << std::endl;
	s3.detailed_print();
}

static void
setters(Student& s3)
{
	s3.set_AM("010101");
	s3.set_name("AAAA");
	s3.set_semester(100);
	s3.set_pcourses(2);
	float *gg = new float[2]{0.1f, 2.2f};
	s3.set_grades(gg);
	delete[] gg;

	std::cout << "Setters example using s3" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: 010101" << std::endl;;
	std::cout << "New AM: " << s3.get_AM() << std::endl;
	std::cout << std::endl;
	std::cout << "Input: AAAA" << std::endl;
	std::cout << "New name: " << s3.get_name() << std::endl;
	std::cout << std::endl;
	std::cout << "Input: 100" << std::endl;
	std::cout << "New semester: " << s3.get_semester() << std::endl;
	std::cout << std::endl;
	std::cout << "Input: 2" << std::endl;
	std::cout << "New courses passed: " << s3.get_pcourses() << std::endl;
	std::cout << std::endl;
	std::cout << "Input: 0.1, 2.2" << std::endl;
	std::cout << "New grades: ";

	float *gr = s3.get_grades();
	if (gr != nullptr)
	{
		for (unsigned int i = 0; i < s3.get_pcourses(); i++)
		{
			if (i != s3.get_pcourses()-1)	std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl << std::endl;
		}
	}
}

static void
addgrd(Student& s3)
{
	s3.add_grade(7.5f);
	float *gr = s3.get_grades();
	if (gr != nullptr)
	{
		std::cout << "Input: 7.5" << std::endl;
		std::cout << "Updated grades: ";
		for (unsigned int i = 0; i < s3.get_pcourses(); i++)
		{
			if (i != s3.get_pcourses()-1) std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl;
		}
	}
}
