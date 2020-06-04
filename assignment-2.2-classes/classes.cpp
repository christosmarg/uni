#include <algorithm>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>

class Student
{
    private:
        char *id;
        std::string name;
        unsigned int semester;
        unsigned int pcourses;
        float *grades;

    public:
        Student(const char *id, const std::string& name);
        Student(const char *id, const std::string& name,
                const unsigned int semester);
        Student(const char *id, const std::string& name,
                const unsigned int semester,
                const unsigned int pcourses,
                const float *grades);
        Student(const Student& s);
        ~Student();

        const std::string& get_name() const;
        constexpr const char *get_id() const;
        constexpr const unsigned int get_semester() const;
        constexpr const unsigned int get_pcourses() const;
        constexpr float *get_grades() const;

        void set_id      (const char *id);
        void set_name    (const std::string& name);
        void set_semester(const unsigned int semester);
        void set_pcourses(const unsigned int pcourses);
        void set_grades  (const float *grades);

        void add_grade(const float grade);
        void detailed_print() const;

    private:
        template<typename T> T *conv(const T *arr, std::size_t len) const;
        template<typename T> T *resize(const T *arr, std::size_t len);
        constexpr std::size_t len(const char *s) const;
        float avg() const;
};

Student::Student(const char *id, const std::string& name)
    :id(conv<char>(id, len(id))), name(name), semester(1), pcourses(0),
    grades(nullptr) {}

Student::Student(const char *id, const std::string& name,
        const unsigned int semester)
    :id(conv<char>(id, len(id))), name(name), semester(semester), pcourses(0),
    grades(nullptr) {}

Student::Student(const char *id, const std::string& name,
        const unsigned int semester,
        const unsigned int pcourses, const float *grades)
    :id(conv<char>(id, len(id))), name(name), semester(semester), pcourses(pcourses),
    grades(conv<float>(grades, pcourses)) {}

Student::Student(const Student& s)
    :name(s.name), semester(s.semester), pcourses(s.pcourses)
{
    this->id = conv<char>(s.id, len(s.id));
    this->grades = conv<float>(s.grades, s.pcourses);
}

Student::~Student()
{
    if (this->id != nullptr)
    {
        delete[] this->id;
        this->id = nullptr;
    }
    if (this->id != nullptr)
    {
        delete[] this->grades;
        this->grades = nullptr; 
    }
}

const std::string&
Student::get_name() const
{
    return this->name;
}

constexpr const char *
Student::get_id() const
{
    return this->id;
}

constexpr const unsigned int
Student::get_semester() const
{
    return this->semester;
}

constexpr const unsigned int
Student::get_pcourses() const
{
    return this->pcourses;
}

constexpr float *
Student::get_grades() const
{
    return this->grades;
}

void
Student::set_id(const char *id)
{
    if (this->id != nullptr) delete[] this->id;
    this->id = conv<char>(id, len(id));
}

void
Student::set_name(const std::string& name)
{
    this->name = name;
}

void
Student::set_semester(const unsigned int semester)
{
    this->semester = semester;
}

void
Student::set_pcourses(const unsigned int pcourses)
{
    this->pcourses = pcourses;
}

void
Student::set_grades(const float *grades)
{
    this->grades = conv<float>(grades, pcourses);
}

void
Student::add_grade(const float grade)
{
    float *tmp = resize<float>(grades, pcourses);
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
        std::cout << "Average grade: " << std::setprecision(2) << avg() << std::endl;
    }
}

constexpr std::size_t
Student::len(const char *s) const
{
    return std::strlen(s) + 1;
}

float
Student::avg() const
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

template<typename T> T *
Student::conv(const T *arr, std::size_t len) const
{
    if (arr != nullptr)
    {
        T *tmp = new T[len];
        std::memcpy(tmp, arr, sizeof(T) * len);
        return tmp;
    }
    else return nullptr;
}

template<typename T> T *
Student::resize(const T *arr, std::size_t len)
{
    T *tmp = new T[len+1];
    if (arr != nullptr)
    {
        std::memcpy(tmp, arr, sizeof(T) * len);
        delete[] arr;
    }
    return tmp;
}

static std::ostream& operator<< (std::ostream& stream, const Student& s);
static void cont();
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

    std::unique_ptr<float[]> grd(new float[4]{9.4f, 8.4f, 5.5f, 6.3f});
    std::unique_ptr<Student> s3 = 
        std::make_unique<Student>("72345678", std::string("Name Surnaming"), 2, 4, grd.get());
    constructor3(*s3); cont();
    detprint(*s3); cont();
    setters(*s3);
    addgrd(*s3); cont();

    return 0;
}

std::ostream&
operator<< (std::ostream& stream, const Student& s)
{
    return stream <<
        "ID: " << s.get_id() << std::endl <<
        "Name: " << s.get_name() << std::endl <<
        "Semester: " << s.get_semester() << std::endl;
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
constructor3(const Student& s3)
{
    std::cout << "Constructor for s3 (ID, Name, Semester, Courses passed, Grades)" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "ID: " << s3.get_id() << std::endl;
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

void
detprint (const Student& s3)
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
    std::unique_ptr<float> gg(new float[2]{0.1f, 2.2f});
    s3.set_grades(gg.get());

    std::cout << "Setters example using s3" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Input: 010101" << std::endl;;
    std::cout << "New ID: " << s3.get_id() << std::endl;
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
            if (i != s3.get_pcourses()-1)   std::cout << gr[i] << ", ";
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
        std::cout << "Updated grades: ";
        for (unsigned int i = 0; i < s3.get_pcourses(); i++)
        {
            if (i != s3.get_pcourses()-1) std::cout << gr[i] << ", ";
            else std::cout << gr[i] << std::endl;
        }
    }
}
