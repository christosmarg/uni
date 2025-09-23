#include "student.h"
#include "subject.h"

inline std::ostream& operator<< (std::ostream& stream, const Student& s)
{
	return stream << "AM: " << s.get_AM() << std::endl << "Name: " << s.get_name() << std::endl;
}

void cont();
void constructor1(const Student& s1);
void ostream_overload(const Student& s1);
void constructor2(const Student& s2);
void copy_constructor(const Student& copystud);
void conditional_overload(const Student& s1, const Student& s2, const Student& copystud);
void constructor3(const Student& s3);
void detprint (const Student& s3);
void setters(Student& s3);
void getters(const Subject& s3);
void setters(Subject& sb);


int main(int argc, char **argv)
{
	Student *s1 = new Student("12345678", "Name Surname");
	system("clear");
	constructor1(*s1); cont();
	ostream_overload(*s1); cont();

	Student *s2 = new Student("12345678", "Name Surname", 2);
	constructor2(*s2); cont();

	Student *copystud = new Student(*s2);
	copy_constructor(*copystud); cont();
	conditional_overload(*s1, *s2, *copystud); cont();
	delete s1;
	delete copystud;
	delete s2;

	float grd[4] = {9.4f, 8.4f, 5.5f, 6.3f};
	Student *s3 = new Student("12345678", "Name Surname", 2, 4, grd);
	constructor3(*s3); cont();
	detprint(*s3); cont();
	setters(*s3); cont();
	delete s3;

	Subject *sb = new Subject("35643", "OOP", 2);
	getters(*sb); cont();
	setters(*sb); 
	delete sb;

	return 0;
}

void cont()
{
	std::cout << std::endl;
	std::cout << "Press <ENTER> to continue. . .";
	if (std::cin.get()) system("clear");
}

void constructor1(const Student& s1)
{
	std::cout << "Constructor for s1 (AM, Name)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "s1.get_AM(): " << s1.get_AM() << std::endl;
	std::cout << "s1.get_name(): " << s1.get_name() << std::endl;
	std::cout << "s1.get_semester(): " << s1.get_semester() << std::endl;
	std::cout << "s1.get_psubj(): " << s1.get_psubj() << std::endl << std::endl;
}

void ostream_overload(const Student& s1)
{
	std::cout << "std::ostream overload" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << s1 << std::endl;
}

void constructor2(const Student& s2)
{
	std::cout << "Constructor for s2 (AM, Name, Semester)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "s2.get_AM(): " << s2.get_AM() << std::endl;
	std::cout << "s2.get_name(): " << s2.get_name() << std::endl;
	std::cout << "s2.get_semester(): " << s2.get_semester() << std::endl;
	std::cout << "s2.get_psubj(): " << s2.get_psubj() << std::endl << std::endl;
}

void copy_constructor(const Student& copystud)
{
	std::cout << "Copy Constructor using copystud object as a copy of s2" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "copystud.get_AM(): " << copystud.get_AM() << std::endl;
	std::cout << "copystud.get_name(): " << copystud.get_name() << std::endl;
	std::cout << "copystud.get_semester(): " << copystud.get_semester() << std::endl;
	std::cout << "copystud.get_psubj(): " << copystud.get_psubj() << std::endl << std::endl;
}

void conditional_overload(const Student& s1, const Student& s2, const Student& copystud)
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

void constructor3(const Student& s3)
{
	std::cout << "Constructor for s3 (AM, Name, Semester, Subjects Passed, Grades)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "s3.get_AM(): " << s3.get_AM() << std::endl;
	std::cout << "s3.get_name(): " << s3.get_name() << std::endl;
	std::cout << "s3.get_semester(): " << s3.get_semester() << std::endl;
	std::cout << "s3.get_psubj(): " << s3.get_psubj() << std::endl;

	float *gr = s3.get_grades();
	std::cout << "s3.get_grades(): ";
	for (int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1) std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl << std::endl;
	}
}

void detprint (const Student& s3)
{
	std::cout << "Detailed print of s3's grades" << std::endl;
	std::cout << "----------------------------" << std::endl;
	s3.detailed_print();
}

void setters(Student& s3)
{
	s3.set_AM("01010101");
	s3.set_name("AAAAAAA");
	s3.set_semester(100);
	s3.set_psubj(2); // πρώτα η set_psubj() και μετα η set_grades() !!!!!
	float gg[2] = {0.1f, 2.2f};
	s3.set_grades(gg);

	std::string ss[3] = {"Math", "Physics", "Programming"};
	s3.set_num_submitted_subjects(3);
	s3.set_submitted_subjects(ss);

	std::cout << "Setters example using s3" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: s3.set_AM(\"01010101\")" << '\t';
	std::cout << "Output: s3.get_AM(): " << s3.get_AM() << std::endl;
	std::cout << "Input: s3.set_name(\"AAAAAAA\")" << '\t';
	std::cout << "Output: s3.get_name(): " << s3.get_name() << std::endl;
	std::cout << "Input: s3.set_semester(100):" << '\t';
	std::cout << "Output: s3.get_semester(): " << s3.get_semester() << std::endl;
	std::cout << "Input: s3.set_psubj(2):" << '\t';
	std::cout << "Output: s3.get_psubj(): " << s3.get_psubj() << std::endl;

	float *gr = s3.get_grades();
	std::cout << "Input: {0.1f, 2.2f}" << '\t' << '\t';
	std::cout << "Output: s3.get_grades(): ";
	for (int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1)	std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl;
	}
	s3.add_grade(7.5f);
	gr = s3.get_grades();
	std::cout << "Input: s3.add_grade(7.5f)" << '\t';
	std::cout << "Output: s3.get_grades(): ";
	for (int i = 0; i < s3.get_psubj(); i++)
	{
		if (i != s3.get_psubj()-1) std::cout << gr[i] << ", ";
		else std::cout << gr[i] << std::endl;
	}
	
	std::cout << std::endl;
	std::cout << "Input: s3.set_num_submitted_subjects(3)" << std::endl;;
	std::cout << "Output: s3.get_num_submitted_subjects(): " << s3.get_num_submitted_subjects() << std::endl << std::endl;

	std::string *ssj = s3.get_submitted_subjects();
	std::cout << "Input: {\"Math\", \"Physics\", \"Programming\"}" << std::endl;;
	std::cout << "Output: s3.get_submitted_subjects(): ";
	for (int i = 0; i < s3.get_num_submitted_subjects(); i++)
	{
		if (i != s3.get_num_submitted_subjects()-1) std::cout << ssj[i] << ", ";
		else std::cout << ssj[i] << std::endl;
	}
}

void getters(const Subject& sb)
{
	std::cout << "Getters example using Subject object" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Constructor: Subject(\"35643\", \"OOP\", 2)" << std::endl;
	std::cout << "sb.get_code(): " << sb.get_code() << std::endl;
	std::cout << "sb.get_sname(): " << sb.get_sname() << std::endl;
	std::cout << "sb.get_subjsemester(): " << sb.get_subjsemester() << std::endl;
}

void setters(Subject& sb)
{
	sb.set_code("14556");
	sb.set_sname("Calculus I");
	sb.set_subjsemester(1);

	std::cout << "Setters example using Subject object" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: sb.set_code(\"14556\")" << '\t' << '\t';
	std::cout << "Output: sb.get_code(): " << sb.get_code() << std::endl;
	std::cout << "Input: sb.set_sname(\"Calculus I\")" << '\t';
	std::cout << "Output: sb.get_sname(): " << sb.get_sname() << std::endl;
	std::cout << "Input: sb.set_subjsemester(1):" << '\t' << '\t';
	std::cout << "Output: sb.get_subjsemester(): " << sb.get_subjsemester() << std::endl;
}
