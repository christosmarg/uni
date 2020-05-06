#include <fstream>
#include <vector>
#include "xstring.h"

int main(int argc, char **argv)
{
	std::ifstream f("res/grades.csv");
	while (f.good())
	{
		lab::xstring a, b, c;
		lab::getline(f, a, ';');
		lab::getline(f, b, ';');
		lab::getline(f, c);
		if (f.eof()) break;
		std::cout << a << " " << b << " " << std::atof(c.cstr()) << std::endl;
	}
	f.close();

	return 0;
}
