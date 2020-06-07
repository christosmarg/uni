#include <memory>
#include "student.hpp"

static std::ostream& operator<< (std::ostream& stream, const Student& s);
static void cont();
static void constructor1(const Student& s1);
static void ostream_overload(const Student& s1);
static void constructor2(const Student& s2);
static void copy_constructor(const Student& copystud);
static void conditional_overload(const Student& s1, const Student& s2, const Student& copystud);
static void equals_overload(const Student& s1, Student& s2);
static void constructor3(const Student& s3);
static void detprint(const Student& s3);
static void setters(Student& s3);
static void addgrd(Student& s3);
static void submcourses(Student& s3);
static void plusequals_overload(Student& s3, Course *c);
static void getters(const Course& s3);
static void setters(Course& c);

/*
 * main uses smart pointers since there are quite a few dynamically
 * allocated objects and so it looks cleaner to let them handle the
 * deletions.
 */
int
main(int argc, char **argv)
{
    std::unique_ptr<Student> s1 = 
        std::make_unique<Student>("12345678", std::string("Name Surname"));
    system("clear || cls");
    constructor1(*s1); cont();
    ostream_overload(*s1); cont();
    
    std::unique_ptr<Student> s2 = 
        std::make_unique<Student>("92345678", std::string("Name Surnamington"), 2);
    constructor2(*s2); cont();

    std::unique_ptr<Student> copystud = std::make_unique<Student>(*s2);
    copy_constructor(*copystud); cont();
    conditional_overload(*s1, *s2, *copystud); cont();
    equals_overload(*s1, *s2); cont();

    std::unique_ptr<float[]> grd(new float[4]{9.4f, 8.4f, 5.5f, 6.3f});
    std::unique_ptr<Student> s3 = std::make_unique<Student>("72345678",
            std::string("Name Surnaming"), 2, 4, grd.get());
    constructor3(*s3); cont();
    detprint(*s3); cont();
    setters(*s3);
    addgrd(*s3); cont();
    submcourses(*s3); cont();

    std::unique_ptr<Student> s4 = std::make_unique<Student>(*s3);
    std::unique_ptr<Course> oop =
        std::make_unique<Course>(std::string("356431"), std::string("OOP"), 2);
    plusequals_overload(*s3, oop.get()); cont();
    getters(*oop); cont();
    setters(*oop); 

    return 0;
}

std::ostream&
operator<< (std::ostream& stream, const Student& s)
{
    return stream <<
        "ID: " << s.get_id() << std::endl <<
        "Name: " << s.get_name() << std::endl <<
        "Semester: " << s.get_semester();
}

void
cont()
{
    std::cout << std::endl;
    std::cout << "Press <ENTER> to continue. . .";
    if (std::cin.get()) system("clear || cls");
}

void
constructor1(const Student& s1)
{
    std::cout << "Constructor for s1 (ID, Name)" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "ID: " << s1.get_id() << std::endl;
    std::cout << "Name: " << s1.get_name() << std::endl;
    std::cout << "Semester (default value): " << s1.get_semester() << std::endl;
    std::cout << "Courses passed (default value): " << s1.get_pcourses() << std::endl;
}

void
ostream_overload(const Student& s1)
{
    std::cout << "std::ostream overload" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << s1 << std::endl;
}

void
constructor2(const Student& s2)
{
    std::cout << "Constructor for s2 (ID, Name, Semester)" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "ID: " << s2.get_id() << std::endl;
    std::cout << "Name: " << s2.get_name() << std::endl;
    std::cout << "Semester: " << s2.get_semester() << std::endl;
    std::cout << "Courses passed (default value): " << s2.get_pcourses() << std::endl;
}

void
copy_constructor(const Student& copystud)
{
    std::cout << "Copy Constructor using copystud object as a copy of s2" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "ID: " << copystud.get_id() << std::endl;
    std::cout << "Name: " << copystud.get_name() << std::endl;
    std::cout << "Semester: " << copystud.get_semester() << std::endl;
    std::cout << "Courses passed (default value): " << copystud.get_pcourses() << std::endl;
}

void
conditional_overload(const Student& s1, const Student& s2, const Student& copystud)
{
    std::cout << "Conditional operator overloading" << std::endl;
    std::cout << "----------------------------" << std::endl;
    if (s2 == copystud) std::cout << "s2 == copystud" << std::endl;
    if (s1 != s2)       std::cout << "s1 != s2" << std::endl;
    if (s1 < s2)        std::cout << "s1 < s2" << std::endl;
    if (s1 <= s2)       std::cout << "s1 <= s2" << std::endl;
    if (s2 > s1)        std::cout << "s2 > s1" << std::endl;
    if (s2 >= s1)       std::cout << "s2 >= s1" << std::endl;
    std::cout << std::endl;
}

void
equals_overload(const Student& s1, Student& s2)
{
    s2 = s1;
    std::cout << "= operator overload (s2 = s1)" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "ID: " << s2.get_id() << std::endl;
    std::cout << "Name: " << s2.get_name() << std::endl;
    std::cout << "Semester: " << s2.get_semester() << std::endl;
    std::cout << "Courses passed (default value): " << s2.get_pcourses() << std::endl;
}

void
constructor3(const Student& s3)
{
    std::cout << "Constructor for s3 (ID, Name, Semester, Courses passed, Grades)" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "ID: " << s3.get_id() << std::endl;
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

void
detprint(const Student& s3)
{
    std::cout << "Detailed print of s3's grades" << std::endl;
    std::cout << "----------------------------" << std::endl;
    s3.detailed_print();
}

void
setters(Student& s3)
{
    s3.set_id("010101");
    s3.set_name("AAAA");
    s3.set_semester(100);
    s3.set_pcourses(2);
    std::unique_ptr<float[]> gg(new float[2]{0.1f, 2.2f});
    s3.set_grades(gg.get());

    std::cout << "Setters example using s3" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Input: 010101 " << std::endl;
    std::cout << "New ID: " << s3.get_id() << std::endl;
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

void
addgrd(Student& s3)
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

void
submcourses(Student& s3)
{
    Course *a = new Course(std::string("11231"), std::string("Discrete Math"), 1);
    Course *b = new Course(std::string("56562"), std::string("Physics"), 1);
    Course *c[] = {a, b};
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

void
plusequals_overload(Student& s3, Course *c)
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

void
getters(const Course& c)
{
    std::cout << "Getters example using Course object" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Constructor: Course(\"356431\", \"OOP\", 2)" << std::endl;
    std::cout << "Code: " << c.get_code() << std::endl;
    std::cout << "Course name: " << c.get_cname() << std::endl;
    std::cout << "Course semester: " << c.get_csemester() << std::endl;
}

void
setters(Course& c)
{
    c.set_code(std::string("14556"));
    c.set_cname(std::string("Calculus I"));
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
