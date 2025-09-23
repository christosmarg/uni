#include "appsystem.h"

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
	std::ifstream f;
	// bug???
	//f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		f.open(fpath, std::ios::in);
		if (f.is_open())
		{
			std::string skip;
			std::getline(f, skip);
			while (f.good())
			{
				std::string sn, name, email;
				std::getline(f, sn, ',');
				std::getline(f, name, ',');
				std::getline(f, email, ',');
				if (f.eof()) break;
				std::cout << sn << " " << name << " " << email << std::endl;
				manfs.push_back(new Manufacturer(sn.c_str(), name.c_str(), email));	
			}
		}
		f.close();
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << "Error reading file \'" << fpath << "\'." << std::endl <<
			e.what() << std::endl;
		return false;
	}
	return true;
}

bool AppSystem::export_data(const char *fpath)
{
	std::ofstream f;
	f.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		f.open(fpath);
		//while (f.good())
		//{

		//}
		f.close();
	}
	catch (const std::ofstream::failure& e)
	{
		std::cerr << "Error writing to file \'" << fpath << "\'." << std::endl <<
			e.what() << std::endl;
		return false;
	}
	return true;
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
			app->set_serialnum(serialnum);
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

void AppSystem::chgenre(const std::string& appname, const std::string& genre)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			if (Game *o = dynamic_cast<Game *>(app))
				o->set_genre(genre);
}

void AppSystem::chonline(const std::string& appname, bool online)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			if (Game *o = dynamic_cast<Game *>(app))
				o->set_online(online);
}

void AppSystem::chexts(const std::string& appname, const std::vector<std::string> exts)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			if (Office *o = dynamic_cast<Office *>(app))
				o->set_exts(exts);
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

void AppSystem::removebad(const char *manfname)
{
	apps.erase(std::remove_if(apps.begin(), apps.end(), [&](App *app)
		{
			Manufacturer m = app->get_manf();
			if (strcmp(m.get_name(), manfname) == 0)
				delete app;
			return strcmp(m.get_name(), manfname) == 0;
		}), apps.end());	
}

const std::vector<Office *> AppSystem::get_freeapps() const
{
	std::vector<Office *> fapps;
	for (auto& app : apps)
		if (Office *o = dynamic_cast<Office *>(app))
			if (o->get_price() == 0)
				fapps.push_back(o);
	return fapps;
}

const std::vector<Game *> AppSystem::get_goodgames() const
{
	std::vector<Game *> ggames;
	for (auto& app : apps)
	{
		if (Game *o = dynamic_cast<Game *>(app))
		{
			std::vector<Review *> revs = o->get_revs();
			int sum = 0, count = 0;	
			for (auto& rev : revs)
			{
				if (rev->get_stars() > 4)
				{
					sum += rev->get_stars();
					count++;
				}
			}
			if (sum / count > 4) ggames.push_back(o);
		}
	}
	return ggames;
}

const std::vector<App *>& AppSystem::get_apps() const
{
	return apps;
}

const std::vector<Manufacturer *>& AppSystem::get_manfs() const
{
	return manfs;
}
