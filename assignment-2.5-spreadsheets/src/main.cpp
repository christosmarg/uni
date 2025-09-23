#include "xstring.h"
#include <fstream>

int main(int argc, char **argv)
{
	std::ifstream f("src/main.cpp");
	while (f.good())
	{
		lab::xstring a;
		lab::getline(f, a);
		std::cout << a << std::endl;
	}
	f.close();

	return 0;
}
