#include <iostream>
#include <string>

class Human
{
	private:
		std::string name;
		int age;

	public:
		Human(std::string name) {this->name = name;}
		std::string getname() const {return name;}
};

int modconst(int *, int);
void chnames(std::string *, int);
void getnames(std::string *, int);
int chval(int &, int);
int& ref(int *, int);
std::string defaultargs(std::string = "No");

int main(int argc, char **argv)
{
	// Ερώτημα 1 
	const int x = 10;
	std::cout << "Old const value: " << x << std::endl << "New const value: " << modconst((int *)&x, 15) << std::endl << std::endl;

	// Ερώτημα 2
	Human *human = new Human("Christos");
	std::string *names = new std::string[3];
	std::cout << human->getname() << std::endl << std::endl;

	chnames(names, 3);
	std::cout << std::endl;
	getnames(names, 3);
	std::cout << std::endl;

	delete human;
	delete[] names;

	// Ερώτημα 3
	int y = 5;
	std::cout << "Old y value: " << y << std::endl << "New y value: " << chval(y, 10) << std::endl << std::endl;

	int	*arr = new int[3];
	for (int i = 0; i < 2; i++) arr[i] = i;
	std::cout << "Old value at index 1: " << arr[1] << std::endl;
	ref(arr, 1) = 500;
	std::cout << "New value at index 1: " << arr[1] << std::endl << std::endl;
	delete[] arr;

	// Ερώτημα 4
	std::cout << "Function return values: " << std::endl;
	std::cout << "With default arg: " << defaultargs() << std::endl;
	std::cout << "Without default arg: " << defaultargs("Yes") << std::endl; 

	return 0;
}

void chnames(std::string *names, int numNames)
{
	for (int i = 0; i < numNames; i++)
	{
		std::cout << "Name " << i << ": ";
		std::cin >> names[i];
	}
}

void getnames(std::string *names, int numNames)
{
	for (int i = 0; i < numNames; i++)
		std::cout << "Name " << i << ": " << names[i] << std::endl;
}

int modconst(int *x, int newVal) {return *x = newVal;}
int chval(int &y, int newVal) {return y = newVal;}
int& ref(int *arr, int index) {return arr[index];}
std::string defaultargs(std::string arg) {return arg;}
