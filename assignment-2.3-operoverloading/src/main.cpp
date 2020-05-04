#include "student.h"

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
static void conditional_overload(const Student& s1, const Student& s2, const Student& copystud);
static void equals_overload(const Student& s1, Student& s2);
static void constructor3(const Student& s3);
static void detprint (const Student& s3);
static void setters(Student& s3);
static void addgrd(Student& s3);
static void submsubj(Student& s3);
static void plusequals_overload(Student& s3, Subject *s);
static void getters(const Subject& s3);
static void setters(Subject& sb);

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
	submsubj(*s3); cont();
	Student *s4 = new Student(*s3);

	std::string c = "356431";
	std::string n = "OOP";
	Subject *oop = new Subject(c, n, 2);
	plusequals_overload(*s3, oop); cont();

	getters(*oop); cont();
	setters(*oop); 

	delete s4;
	delete s3;
	delete oop;

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
	std::cout << "= operator overload using s2 = s1" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s2.get_AM() << std::endl;
	std::cout << "Name: " << s2.get_name() << std::endl;
	std::cout << "Semester: " << s2.get_semester() << std::endl;
	std::cout << "Subjects passed (default value): " << s2.get_psubj() << std::endl << std::endl;
}

static void constructor3(const Student& s3)
{
	std::cout << "Constructor for s3 (AM, Name, Semester, Subjects passed, Grades)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "AM: " << s3.get_AM() << std::endl;
	std::cout << "Name: " << s3.get_name() << std::endl;
	std::cout << "Semester: " << s3.get_semester() << std::endl;
	std::cout << "Subjects passed: " << s3.get_psubj() << std::endl;

	float *gr = s3.get_grades();
	if (gr != nullptr)
	{
		std::cout << "Grades: ";
		for (unsigned int i = 0; i < s3.get_psubj(); i++)
		{
			if (i != s3.get_psubj()-1) std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl << std::endl;
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
	if (gr != nullptr)
	{
		std::cout << "Input: {0.1f, 2.2f}" << '\t' << '\t';
		std::cout << "New grades: ";
		for (unsigned int i = 0; i < s3.get_psubj(); i++)
		{
			if (i != s3.get_psubj()-1)	std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl;
		}
	}
}

static void addgrd(Student& s3)
{
	s3.add_grade(7.5f);
	float *gr = s3.get_grades();
	if (gr != nullptr)
	{
		std::cout << "Input: s3.add_grade(7.5f)" << '\t';
		std::cout << "Updated grades: ";
		for (unsigned int i = 0; i < s3.get_psubj(); i++)
		{
			if (i != s3.get_psubj()-1) std::cout << gr[i] << ", ";
			else std::cout << gr[i] << std::endl;
		}
	}
}

static void submsubj(Student& s3)
{
	std::string c1 = "11231";
	std::string c2 = "56562";
	std::string n1 = "Discrete Math";
	std::string n2 = "Physics";
	
	Subject *a = new Subject(c1, n1, 1);
	Subject *b = new Subject(c2, n2, 1);
	Subject **sb = new Subject *[2]{a, b};
	s3.set_num_submitted_subjects(2);
	s3.set_submitted_subjects(sb);

	std::cout << "Submitted subjects example" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: s3.set_num_submitted_subjects(2)" << std::endl;
	std::cout << "Number of submitted subjects: " << s3.get_num_submitted_subjects() << std::endl << std::endl;
	
	Subject **ssj = s3.get_submitted_subjects();
	if (ssj != nullptr)
	{
		std::cout << "Input: {\"Discrete Math\", \"Physics\"}" << std::endl;
		std::cout << "Submitted subjects: ";
		for (unsigned int i = 0; i < s3.get_num_submitted_subjects(); i++)
		{
			if (i != s3.get_num_submitted_subjects()-1) std::cout << ssj[i][0].get_sname() << ", ";
			else std::cout << ssj[i][0].get_sname() << std::endl;
		}
	}
}

static void plusequals_overload(Student& s3, Subject *s)
{
	s3 += s;
	Subject **ssj = s3.get_submitted_subjects();
	if (ssj != nullptr)
	{
		std::cout << "+= operator overload" << std::endl;
		std::cout << "----------------------------" << std::endl;
		std::cout << "Input: s3 += \"OOP\"" << std::endl;;
		std::cout << "Updated submitted subjects: ";
		for (unsigned int i = 0; i < s3.get_num_submitted_subjects(); i++)
		{
			if (i != s3.get_num_submitted_subjects()-1) std::cout << ssj[i][0].get_sname() << ", ";
			else std::cout << ssj[i][0].get_sname() << std::endl;
		}
	}
}

static void getters(const Subject& sb)
{
	std::cout << "Getters example using Subject object" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Constructor: Subject(\"356431\", \"OOP\", 2)" << std::endl;
	std::cout << "Code: " << sb.get_code() << std::endl;
	std::cout << "Subject name: " << sb.get_sname() << std::endl;
	std::cout << "Subject semester: " << sb.get_subjsemester() << std::endl;
}

static void setters(Subject& sb)
{
	std::string c = "14556";
	std::string n = "Calculus I";

	sb.set_code(c);
	sb.set_sname(n);
	sb.set_subjsemester(1);

	std::cout << "Setters example using Subject object" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: sb.set_code(\"14556\")" << '\t' << '\t';
	std::cout << "New code: " << sb.get_code() << std::endl;
	std::cout << "Input: sb.set_sname(\"Calculus I\")" << '\t';
	std::cout << "New subject name: " << sb.get_sname() << std::endl;
	std::cout << "Input: sb.set_subjsemester(1):" << '\t' << '\t';
	std::cout << "New subject semester: " << sb.get_subjsemester() << std::endl;
}
