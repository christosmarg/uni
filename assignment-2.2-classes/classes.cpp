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
			:AM(s.AM), name(s.name), semester(s.semester), psubj(s.psubj), grades(s.grades) {}
		
		~Student()
		{
			delete[] this->AM;
			delete[] this->grades;
		}

		inline const char *get_AM() const {return AM;}
		inline const std::string& get_name() const {return name;}
		inline unsigned int get_semester() const {return semester;}
		inline unsigned int get_psubj() const {return psubj;}
		inline float *get_grades() const {return grades;}

		inline void set_AM(const char *AM) {this->AM = convert_AM(AM);}
		inline void set_name(const std::string& name) {this->name = name;}
		inline void set_semester(unsigned int semester) {this->semester = semester;}
		inline void set_psubj(unsigned int psubj) {this->psubj = psubj;}
		inline void set_grades(float *grades) {this->grades = convert_PSG(grades);}
		inline void print_3first() {std::cout << AM << " " << name << " " << semester << std::endl;}

		char *convert_AM(const char *AM)
		{
			int len = strlen(AM);
			this->AM = new char[len+1];
			std::copy(AM, AM+len, this->AM);
			return this->AM;
		}

		float *convert_PSG(const float *grades)
		{
			this->grades = new float[psubj];
			std::copy(grades, grades+psubj, this->grades);
			return this->grades;	
		}

		void add_grade(float grade)
		{
			float *tmp = new float[psubj+1];
			std::copy(this->grades, this->grades+psubj, tmp);
			tmp[psubj] = grade;
			this->grades = tmp;
			psubj++;
		}

		void detailed_print()
		{
			for (int i = 0; i < psubj; i++)
			{
				std::cout << "Subject " << i+1 << ": ";
				std::cout << grades[i] << std::endl;		
			}
			std::cout << "Average grade: " << std::setprecision(2) << calc_average() << std::endl;
		}

		float calc_average()
		{
			float sum = 0;
			for (int i = 0; i < psubj; i++)
				sum += grades[i];
			float average = sum / psubj;
			return average;
		}
};

int main(int argc, char **argv)
{
	Student *s1 = new Student("19390133", "Christos Margiolis");
	std::cout << "Constructor for s1 (AM, Name)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "s1->get_AM(): " << s1->get_AM() << std::endl;
	std::cout << "s1->get_name(): " << s1->get_name() << std::endl;
	std::cout << "s1->get_semester(): " << s1->get_semester() << std::endl;
	std::cout << "s1->get_psubj(): " << s1->get_psubj() << std::endl << std::endl;
	delete s1;

	Student *s2 = new Student("19390133", "Christos Margiolis", 2);
	std::cout << "Constructor for s2 (AM, Name, Semester)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "s2->get_AM(): " << s2->get_AM() << std::endl;
	std::cout << "s2->get_name(): " << s2->get_name() << std::endl;
	std::cout << "s2->get_semester(): " << s2->get_semester() << std::endl;
	std::cout << "s2->get_psubj(): " << s2->get_psubj() << std::endl << std::endl;

	Student *copystud = new Student(*s2);
	std::cout << "Copy Constructor using copystud object as a copy of s2" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "copystud->get_AM(): " << copystud->get_AM() << std::endl;
	std::cout << "copystud->get_name(): " << copystud->get_name() << std::endl;
	std::cout << "copystud->get_semester(): " << copystud->get_semester() << std::endl;
	std::cout << "copystud->get_psubj(): " << copystud->get_psubj() << std::endl << std::endl;
	delete s2;

	float grd[4] = {9.4f, 8.4f, 5.5f, 6.3f};
	Student *s3 = new Student("19390133", "Christos Margiolis", 2, 4, grd);
	std::cout << "Constructor for s3 (AM, Name, Semester, Subjects Passed, Grades)" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "s3->get_AM(): " << s3->get_AM() << std::endl;
	std::cout << "s3->get_name(): " << s3->get_name() << std::endl;
	std::cout << "s3->get_semester(): " << s3->get_semester() << std::endl;
	std::cout << "s3->get_psubj(): " << s3->get_psubj() << std::endl;

	float *gr = s3->get_grades();
	std::cout << "s3->get_grades(): ";
	for (int i = 0; i < s3->get_psubj(); i++)
	{
		std::cout << gr[i] << ", ";
		if (i == s3->get_psubj()-1)
			std::cout << gr[i] << std::endl << std::endl;
	}

	std::cout << "Detailed print of s3's grades" << std::endl;
	std::cout << "----------------------------" << std::endl;
	s3->detailed_print();

	s3->set_AM("01010101");
	s3->set_name("AAAAAAA");
	s3->set_semester(100);
	s3->set_psubj(2); // πρώτα η set_psubj() και μετα η set_grades() !!!!!
	float gg[2] = {0.1f, 2.2f};
	s3->set_grades(gg);

	std::cout << std::endl;
	std::cout << "Setters example using s3" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Input: s3->set_AM(\"01010101\")" << '\t';
	std::cout << "Output: s3->get_AM(): " << s3->get_AM() << std::endl;
	std::cout << "Input: s3->set_name(\"AAAAAAA\")" << '\t';
	std::cout << "Output: s3->get_name(): " << s3->get_name() << std::endl;
	std::cout << "Input: s3->set_semester(100):" << '\t';
	std::cout << "Output: s3->get_semester(): " << s3->get_semester() << std::endl;
	std::cout << "Input: s3->set_psubj(2):" << '\t';
	std::cout << "Output: s3->get_psubj(): " << s3->get_psubj() << std::endl;

	gr = s3->get_grades();
	std::cout << "Input: {0.1f, 2.2f}" << '\t' << '\t';
	std::cout << "Output: s3->get_grades(): ";
	for (int i = 0; i < s3->get_psubj(); i++)
	{
		std::cout << gr[i] << ", ";
		if (i == s3->get_psubj()-1)
			std::cout << gr[i] << std::endl;
	}

	s3->add_grade(7.5f);
	gr = s3->get_grades();
	std::cout << "Input: s3->add_grade(7.5f)" << '\t';
	std::cout << "Output: s3->get_grades(): ";
	for (int i = 0; i < s3->get_psubj(); i++)
	{
		std::cout << gr[i] << ", ";
		if (i == s3->get_psubj()-1)
			std::cout << gr[i] << std::endl;
	}
	delete s3;

	return 0;
}
