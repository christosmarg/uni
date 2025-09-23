#include "app.h"

App::App()
	:serialnum(nullptr), name(""), os(""), manf(nullptr), price(0) {}

App::App(const char *serialnum, const std::string& name,
	const std::string& os, Manufacturer *manf, int price)
	:serialnum(convsn(serialnum)), name(name), os(os), manf(manf), price(price)
{}

App::~App()
{
	if (serialnum != nullptr) delete[] serialnum;
	if (!reviews.empty()) reviews.clear();
}

char *App::convsn(const char *serialnum)
{
	int len = strlen(serialnum);
	char *tmp = new char[len + 1];
	std::copy(serialnum, serialnum + len + 1, tmp);
	return tmp;	
}

void App::addrev(Review *rev)
{
	reviews.push_back(rev);
}

const char *App::get_serialnum() const
{
	return serialnum;
}

const std::string& App::get_name() const
{
	return name;
}

const std::string& App::get_os() const
{
	return os;
}

const Manufacturer App::get_manf() const
{
	return Manufacturer(*manf);
}

const std::vector<Review *>& App::get_revs() const
{
	return reviews;
}

int App::get_price() const
{
	return price;
}

void App::set_serialnum(const char *serialnum)
{
	if (this->serialnum != nullptr) delete[] serialnum;
	this->serialnum = convsn(serialnum);
}

void App::set_name(const std::string& name)
{
	this->name = name;
}

void App::set_os(const std::string& os)
{
	this->os = os;
}

void App::set_manf(Manufacturer *manf)
{
	this->manf = manf;
}

void App::set_price(int price)
{
	this->price = price;
}
