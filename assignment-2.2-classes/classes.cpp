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
		unsigned int psubj;
		float *grades;
		int size;

	public:
		Student(const char *AM, const std::string& name)
			:AM(convert_AM(AM)), name(name), semester(1), psubj(0) {}

		Student(const char *AM, const std::string& name, unsigned int semester)
			:AM(convert_AM(AM)), name(name), semester(semester), psubj(0) {}

		Student(const char *AM, const std::string& name, unsigned int semester,
				unsigned int psubj, const float *grades)
			:AM(convert_AM(AM)), name(name), semester(semester), psubj(psubj), grades(convert_PSG(grades)) {}

		Student(const Student& s)
			:name(s.name), semester(s.semester), psubj(s.psubj)
		{
			int sl = strlen(s.AM);
			AM = new char[sl + 1];
			std::copy(s.AM, s.AM+sl, AM);

			grades = new float[psubj];
			std::copy(s.grades, s.grades+psubj, grades);
		}
		
		~Student()
		{
			delete[] this->AM;
			delete[] this->grades;
		}

		friend std::ostream& operator<< (std::ostream& stream, const Student& s); 

		inline const char *get_AM() const {return AM;}
		inline const std::string& get_name() const {return name;}
		inline unsigned int get_semester() const {return semester;}
		inline unsigned int get_psubj() const {return psubj;}
		float *get_grades() const;

		inline void set_AM(const char *AM) {this->AM = convert_AM(AM);}
		inline void set_name(const std::string& name) {this->name = name;}
		inline void set_semester(unsigned int semester) {this->semester = semester;}
		inline void set_psubj(unsigned int psubj) {this->psubj = psubj;}
		inline void set_grades(float *grades) {this->grades = convert_PSG(grades);}

		char *convert_AM(const char *AM);
		float *convert_PSG(const float *grades);
		void add_grade(float grade);
		void detailed_print() const;
		float calc_average() const;
};

float *Student::get_grades() const
{
	float *ret = new float[psubj];
	std::copy(grades, grades+psubj, ret);
	return ret;
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

std::ostream& operator<< (std::ostream& stream, const Student& s)
{
	return stream << "AM: " << s.get_AM() << std::endl << "Name: " << s.get_name() << std::endl 
		<< "Semester: " << s.get_semester() << std::endl;
}

static void cont();
static void constructor1(const Student& s1);
static void ostream_overload(const Student& s1);
static void constructor2(const Student& s2);
static void copy_constructor(const Student& copystud);
static void constructor3(const Student& s3);
static void detprint (const Student& s3);
static void setters(Student& s3);
static void addgrd(Student& s3);

int main(int argc, char **argv)
{
	Student *s1 = new Student("12345678", "Name Surname");
	system("clear");
	constructor1(*s1); cont();
	ostream_overload(*s1); cont();
	delete s1;

	Student *s2 = new Student("92345678", "Name Surnamington", 2);
	constructor2(*s2); cont();

	Student *copystud = new Student(*s2);
	copy_constructor(*copystud); cont();
	delete copystud;
	delete s2;

	float grd[4] = {9.4f, 8.4f, 5.5f, 6.3f};
	Student *s3 = new Student("72345678", "Name Surnaming", 2, 4, grd);
	constructor3(*s3); cont();
	detprint(*s3); cont();
	setters(*s3);
	addgrd(*s3); cont();
	delete s3;

	return 0;
}

static void cont()
{
	std::cout << std::endl;
	std::cout << "Press <ENTER> to continue. . .";
	if (std::cin.get()) system("clear || cls");
}

static void constructor1(const Student& s1)
{
	std::cout << "Constructor for s1 (AM, Name)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s1.get_AM() << std::endl;
	std::cout << "Name: " << s1.get_name() << std::endl;
	std::cout << "Semester (default value): " << s1.get_semester() << std::endl;
	std::cout << "Subjects passed (default value): " << s1.get_psubj() << std::endl << std::endl;
}

static void ostream_overload(const Student& s1)
{
	std::cout << "std::ostream overload" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << s1 << std::endl;
}

static void constructor2(const Student& s2)
{
	std::cout << "Constructor for s2 (AM, Name, Semester)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s2.get_AM() << std::endl;
	std::cout << "Name: " << s2.get_name() << std::endl;
	std::cout << "Semester: " << s2.get_semester() << std::endl;
	std::cout << "Subjects passed (default value): " << s2.get_psubj() << std::endl << std::endl;
}

static void copy_constructor(const Student& copystud)
{
	std::cout << "Copy Constructor using copystud object as a copy of s2" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << copystud.get_AM() << std::endl;
	std::cout << "Name: " << copystud.get_name() << std::endl;
	std::cout << "Semester: " << copystud.get_semester() << std::endl;
	std::cout << "Subjects passed (default value): " << copystud.get_psubj() << std::endl << std::endl;
}

static void constructor3(const Student& s3)
{
	std::cout << "Constructor for s3 (AM, Name, Semester, Subjects Passed, Grades)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s3.get_AM() << std::endl;
	std::cout << "Name: " << s3.get_name() << std::endl;
	std::cout << "Semester: " << s3.get_semester() << std::endl;
	std::cout << "Subjects passed: " << s3.get_psubj() << std::endl;

	float *gr = new float[s3.get_psubj()];
	gr = s3.get_grades();
	std::cout << "Grades: ";
	for (unsigned int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1) std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl << std::endl;
	}
	delete[] gr;
}

static void detprint (const Student& s3)
{
	std::cout << "Detailed print of s3's grades" << std::endl;
	std::cout << "----------------------------" << std::endl;
	s3.detailed_print();
}

static void setters(Student& s3)
{
	s3.set_AM("01010101");
	s3.set_name("AAAAAAA");
	s3.set_semester(100);
	s3.set_psubj(2); // πρώτα η set_psubj() και μετα η set_grades() !!!!!
	float gg[2] = {0.1f, 2.2f};
	s3.set_grades(gg);

	std::cout << "Setters example using s3" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: s3.set_AM(\"01010101\")" << '\t';
	std::cout << "New AM: " << s3.get_AM() << std::endl;
	std::cout << "Input: s3.set_name(\"AAAAAAA\")" << '\t';
	std::cout << "New name: " << s3.get_name() << std::endl;
	std::cout << "Input: s3.set_semester(100):" << '\t';
	std::cout << "New semester: " << s3.get_semester() << std::endl;
	std::cout << "Input: s3.set_psubj(2):" << '\t' << '\t';
	std::cout << "New subjects passed: " << s3.get_psubj() << std::endl;

	float *gr = new float[s3.get_psubj()];
	gr = s3.get_grades();
	std::cout << "Input: {0.1f, 2.2f}" << '\t' << '\t';
	std::cout << "New grades: ";
	for (unsigned int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1)	std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl;
	}
	delete[] gr;
}

static void addgrd(Student& s3)
{
	s3.add_grade(7.5f);
	float *gr = new float[s3.get_psubj()];
	gr = s3.get_grades();
	std::cout << "Input: s3.add_grade(7.5f)" << '\t';
	std::cout << "Updated grades: ";
	for (unsigned int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1) std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl;
	}
	delete[] gr;
}
