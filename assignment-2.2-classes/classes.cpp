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
			memcpy(AM, s.AM, sizeof(s.AM) + (sl+1));
			this->grades = new float[s.psubj];
			memcpy(grades, s.grades, sizeof(s.grades) * s.psubj);
		}
		
		~Student()
		{
			delete[] this->AM;
			delete[] this->grades;
		}

		friend std::ostream& operator<< (std::ostream& stream, const Student& s); 

		inline const char *get_AM() const {return this->AM;}
		inline const std::string& get_name() const {return this->name;}
		inline unsigned int get_semester() const {return this->semester;}
		inline unsigned int get_psubj() const {return this->psubj;}
		float *get_grades() const {return this->grades;}

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

std::ostream& operator<< (std::ostream& stream, const Student& s)
{
	return stream << "AM: " << s.get_AM() << std::endl << "Name: " << s.get_name() << std::endl 
		<< "Semester: " << s.get_semester() << std::endl;
}

static void cont(void);
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

static void cont(void)
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
	std::cout << "constructor for s3 (am, name, semester, subjects passed, grades)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "am: " << s3.get_AM() << std::endl;
	std::cout << "name: " << s3.get_name() << std::endl;
	std::cout << "semester: " << s3.get_semester() << std::endl;
	std::cout << "subjects passed: " << s3.get_psubj() << std::endl;

	float *gr = s3.get_grades();
	std::cout << "grades: ";
	for (unsigned int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1) std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl << std::endl;
	}
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
	float *gg = new float[2]{0.1f, 2.2f};
	s3.set_grades(gg);
	delete[] gg;

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

	float *gr = s3.get_grades();
	std::cout << "Input: {0.1f, 2.2f}" << '\t' << '\t';
	std::cout << "New grades: ";
	for (unsigned int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1)	std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl;
	}
}

static void addgrd(Student& s3)
{
	s3.add_grade(7.5f);
	float *gr = s3.get_grades();
	std::cout << "Input: s3.add_grade(7.5f)" << '\t';
	std::cout << "Updated grades: ";
	for (unsigned int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1) std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl;
	}
}
