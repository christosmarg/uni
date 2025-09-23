#include <iostream>
#include <string>
#include <vector>

class Student
{
	private:
		std::vector<char> AM;
		std::string name;
		unsigned int semester;
		unsigned int psubj;
		std::vector<float> psubjGrades;

	public:
		Student(const std::vector<char>& AM, const std::string& name)
			:AM(AM), name(name), semester(1), psubj(0) {}

		Student(const std::vector<char>& AM, const std::string& name, unsigned int semester)
			:psubj(0) {}

		Student(const std::vector<char>& AM, const std::string& name, unsigned int semester,
				unsigned int psubj, const std::vector<float>& psubjGrades)
			:AM(AM), name(name), semester(semester), psubj(psubj), psubjGrades(psubjGrades) {}

		Student(const Student& s)
			:AM(s.AM), name(s.name), semester(s.semester), psubj(s.psubj), psubjGrades(s.psubjGrades) {}
		
		~Student() {}
		
		inline const std::vector<char>& get_AM() const {return AM;}
		inline const std::string& get_name() const {return name;}
		inline unsigned int get_semester() const {return semester;}
		inline unsigned int get_psubj() const {return psubj;}
		inline const std::vector<float>& get_psubjGrades() const {return psubjGrades;}

		inline void set_AM(const std::vector<char>& AM) {this->AM = AM;}
		inline void set_name(const std::string& name) {this->name = name;}
		inline void set_semester(unsigned int semester) {this->semester = semester;}
		inline void set_psubj(unsigned int psubj) {this->psubj = psubj;}
		inline void set_psubjGrades(const std::vector<float>& psubjGrades) {this->psubjGrades = psubjGrades;}
		inline void add_grade(float grade) {psubjGrades.push_back(grade);}

		inline void print_3first()
		{
			for (std::size_t i = 0; i < AM.size(); i++)
				std::cout << AM[i];
			std::cout << " " << name << " " << semester << std::endl;
		}
};

int main(int argc, char **argv)
{
	std::vector<char> AM = {'1','9','3','9','0','1','3','3'};
	std::vector<float> psubjGrades = {9.5f, 8.4f, 5.6f};
	Student *s1 = new Student(AM, "Christos Margiolis");
	AM = s1->get_AM();
	std::cout << s1->get_name() << " " << s1->get_semester() << " " << s1->get_psubj() << std::endl;
	delete s1;

	Student *s2 = new Student(AM, "Christos Margiolis", 2);
	s2->set_AM(AM);
	s2->set_name("AAAA");
	s2->set_semester(2);
	s2->set_psubj(3);
	s2->set_psubjGrades(psubjGrades);
	std::cout << s2->get_name() << " " << s2->get_semester() << " " << s2->get_psubj() << std::endl;
	delete s2;

	Student *s3 = new Student(AM, "Christos Margiolis", 2, 3, psubjGrades);
	s3->add_grade(7.5f);
	s3->print_3first();
	std::vector<float>().swap(psubjGrades);
	std::vector<char>().swap(AM);
	delete s3;

	return 0;
}
