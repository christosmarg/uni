#include "student.h"

std::ostream& operator<< (std::ostream& stream, const Student& s);
static void cont(void);
static void constructor1(const Student& s1);
static void ostream_overload(const Student& s1);
static void constructor2(const Student& s2);
static void copy_constructor(const Student& copystud);
static void conditional_overload(const Student& s1, const Student& s2, const Student& copystud);
static void equals_overload(const Student& s1, Student& s2);
static void constructor3(const Student& s3);
static void detprint (const Student& s3);
static void setters(Student& s3);
static void addgrd(Student& s3);
static void submcourses(Student& s3);
static void plusequals_overload(Student& s3, Course *c);
static void getters(const Course& s3);
static void setters(Course& c);

int main(int argc, char **argv)
{
	std::string n1 = "Name Surname";
	std::string n2 = "Name Surnamington";
	std::string n3 = "Name Surnaming";

	Student *s1 = new Student("12345678", n1);
	system("clear || cls");
	constructor1(*s1); cont();
	ostream_overload(*s1); cont();
	
	Student *s2 = new Student("92345678", n2, 2);
	constructor2(*s2); cont();

	Student *copystud = new Student(*s2);
	copy_constructor(*copystud); cont();
	conditional_overload(*s1, *s2, *copystud); cont();
	equals_overload(*s1, *s2); cont();
	delete s1;
	delete copystud;
	delete s2;

	float *grd = new float[4]{9.4f, 8.4f, 5.5f, 6.3f};
	Student *s3 = new Student("72345678", n3, 2, 4, grd);
	delete[] grd;
	constructor3(*s3); cont();
	detprint(*s3); cont();
	setters(*s3);
	addgrd(*s3); cont();
	submcourses(*s3); cont();
	Student *s4 = new Student(*s3);

	std::string c = "356431";
	std::string n = "OOP";
	Course *oop = new Course(c, n, 2);
	plusequals_overload(*s3, oop); cont();

	getters(*oop); cont();
	setters(*oop); 

	delete s4;
	delete s3;
	delete oop;

	return 0;
}

std::ostream& operator<< (std::ostream& stream, const Student& s)
{
	return stream <<
		"AM: " << s.get_AM() << std::endl <<
		"Name: " << s.get_name() << std::endl <<
		"Semester: " << s.get_semester();
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
	std::cout << "Courses passed (default value): " << s1.get_pcourses() << std::endl;
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
	std::cout << "Courses passed (default value): " << s2.get_pcourses() << std::endl;
}

static void copy_constructor(const Student& copystud)
{
	std::cout << "Copy Constructor using copystud object as a copy of s2" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << copystud.get_AM() << std::endl;
	std::cout << "Name: " << copystud.get_name() << std::endl;
	std::cout << "Semester: " << copystud.get_semester() << std::endl;
	std::cout << "Courses passed (default value): " << copystud.get_pcourses() << std::endl;
}

static void conditional_overload(const Student& s1, const Student& s2, const Student& copystud)
{
	std::cout << "Conditional operator overloading" << std::endl;
	std::cout << "----------------------------" << std::endl;
	if (s2 == copystud) std::cout << "s2 == copystud" << std::endl;
	if (s1 != s2) std::cout << "s1 != s2" << std::endl;
	if (s1 < s2) std::cout << "s1 < s2" << std::endl;
	if (s1 <= s2) std::cout << "s1 <= s2" << std::endl;
	if (s2 > s1) std::cout << "s2 > s1" << std::endl;
	if (s2 >= s1) std::cout << "s2 >= s1" << std::endl;
	std::cout << std::endl;
}

static void equals_overload(const Student& s1, Student& s2)
{
	s2 = s1;
	std::cout << "= operator overload (s2 = s1)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s2.get_AM() << std::endl;
	std::cout << "Name: " << s2.get_name() << std::endl;
	std::cout << "Semester: " << s2.get_semester() << std::endl;
	std::cout << "Courses passed (default value): " << s2.get_pcourses() << std::endl;
}

static void constructor3(const Student& s3)
{
	std::cout << "Constructor for s3 (AM, Name, Semester, Courses passed, Grades)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s3.get_AM() << std::endl;
	std::cout << "Name: " << s3.get_name() << std::endl;
	std::cout << "Semester: " << s3.get_semester() << std::endl;
	std::cout << "Courses passed: " << s3.get_pcourses() << std::endl;
	std::cout << "Grades: ";

	float *gr = s3.get_grades();
	if (gr != nullptr)
	{
		for (unsigned int i = 0; i < s3.get_pcourses(); i++)
		{
			if (i != s3.get_pcourses()-1) std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl;
		}
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
	s3.set_AM("010101");
	s3.set_name("AAAA");
	s3.set_semester(100);
	s3.set_pcourses(2);
	float *gg = new float[2]{0.1f, 2.2f};
	s3.set_grades(gg);
	delete[] gg;

	std::cout << "Setters example using s3" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: 010101 " << std::endl;
	std::cout << "New AM: " << s3.get_AM() << std::endl;
	std::cout << std::endl;
	std::cout << "Input: AAAA " << std::endl;
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
			if (i != s3.get_pcourses()-1) std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl << std::endl;
		}
	}
}

static void addgrd(Student& s3)
{
	s3.add_grade(7.5f);
	float *gr = s3.get_grades();
	if (gr != nullptr)
	{
		std::cout << "Input: 7.5" << std::endl;
		std::cout << "Updated new grades: ";
		for (unsigned int i = 0; i < s3.get_pcourses(); i++)
		{
			if (i != s3.get_pcourses()-1) std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl;
		}
	}
}

static void submcourses(Student& s3)
{
	std::string c1 = "11231";
	std::string c2 = "56562";
	std::string n1 = "Discrete Math";
	std::string n2 = "Physics";
	
	Course *a = new Course(c1, n1, 1);
	Course *b = new Course(c2, n2, 1);
	Course **c = new Course *[2]{a, b};
	s3.set_num_submitted_courses(2);
	s3.set_submitted_courses(c);

	std::cout << "Submitted courses example" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: 2" << std::endl;
	std::cout << "Number of submitted courses: " << s3.get_num_submitted_courses();
	std::cout << std::endl << std::endl;
	
	Course **sc = s3.get_submitted_courses();
	if (sc != nullptr)
	{
		std::cout << "Input: Discrete Math, Physics" << std::endl;
		std::cout << "Submitted courses: ";
		for (unsigned int i = 0; i < s3.get_num_submitted_courses(); i++)
		{
			if (i != s3.get_num_submitted_courses()-1) std::cout << sc[i][0].get_cname() << ", ";
			else std::cout << sc[i][0].get_cname() << std::endl;
		}
	}
}

static void plusequals_overload(Student& s3, Course *c)
{
	s3 += c;
	Course **sc = s3.get_submitted_courses();
	if (sc != nullptr)
	{
		std::cout << "+= operator overload" << std::endl;
		std::cout << "----------------------------" << std::endl;
		std::cout << "Input: OOP" << std::endl;;
		std::cout << "Updated submitted courses: ";
		for (unsigned int i = 0; i < s3.get_num_submitted_courses(); i++)
		{
			if (i != s3.get_num_submitted_courses()-1) std::cout << sc[i][0].get_cname() << ", ";
			else std::cout << sc[i][0].get_cname() << std::endl;
		}
	}
}

static void getters(const Course& c)
{
	std::cout << "Getters example using Course object" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Constructor: Course(\"356431\", \"OOP\", 2)" << std::endl;
	std::cout << "Code: " << c.get_code() << std::endl;
	std::cout << "Course name: " << c.get_cname() << std::endl;
	std::cout << "Course semester: " << c.get_csemester() << std::endl;
}

static void setters(Course& c)
{
	std::string code = "14556";
	std::string name = "Calculus I";

	c.set_code(code);
	c.set_cname(name);
	c.set_csemester(1);

	std::cout << "Setters example using Course object" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: 14556" << std::endl;
	std::cout << "New code: " << c.get_code() << std::endl;
	std::cout << std::endl;
	std::cout << "Input: Calculus I" << std::endl;
	std::cout << "New course name: " << c.get_cname() << std::endl;
	std::cout << std::endl;
	std::cout << "Input: 1" << std::endl;
	std::cout << "New course semester: " << c.get_csemester() << std::endl;
}
