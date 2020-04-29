#include "appsystem.h"
#include <iostream>
#include <sstream>

AppSystem::AppSystem() {} 

AppSystem::~AppSystem()
{
	for (auto& app : apps)
		if (app != nullptr)
			delete app;
	if (!apps.empty())
		apps.clear();

	for (auto& manf : manfs)
		if (manf != nullptr)
			delete manf;
	if (!manfs.empty())
		manfs.clear();
}

AppSystem& AppSystem::operator+= (App *app)
{
	apps.push_back(app);
	return *this;
}

AppSystem& AppSystem::operator+= (Manufacturer *man)
{
	manfs.push_back(man);
	return *this;
}

bool AppSystem::read_data(const char *fpath)
{
	std::ifstream f(fpath);
	std::string s;
	while (f.good())
	{
		std::getline(f, s, ',');
		std::cout << s << std::endl; 
	}
}

bool export_data(const char *fpath)
{
	std::ofstream f(fpath);
	while (f.good())
	{
	
	}
}

void AppSystem::newrev(const std::string& appname, Review *rev)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			app->addrev(rev);
}

void AppSystem::chserialnum(const std::string& appname, const char *serialnum)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			app->convsn(serialnum);
}

void AppSystem::chname(const std::string& appname, const std::string& name)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			app->set_name(name);
}

void AppSystem::chos(const std::string& appname, const std::string& os)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			app->set_os(os);
}

void AppSystem::chmanf(const std::string& appname, Manufacturer *manf)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			app->set_manf(manf);
}

void AppSystem::chprice(const std::string& appname, int price)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			app->set_price(price);
}

void AppSystem::removebad(Manufacturer *man)
{
	apps.erase(std::remove_if(apps.begin(), apps.end(), [&](App *app)
		{
			Manufacturer m = app->get_manf();
			if (strcmp(m.get_name(), man->get_name()) == 0)
				delete app;
			return strcmp(m.get_name(), man->get_name()) == 0;
		}), apps.end());	
}

const std::vector<App *>& AppSystem::get_apps() const
{
	return apps;
}

const std::vector<Manufacturer *>& AppSystem::get_manfs() const
{
	return manfs;
}
