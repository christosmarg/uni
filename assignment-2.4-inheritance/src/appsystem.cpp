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

template<>
bool AppSystem::import_data<Manufacturer>(const char *fpath)
{
	std::ifstream f;
	f.exceptions(std::ifstream::badbit);
	try
	{
		std::string strpath(fpath);
		if (!valid_path(strpath)) throw strpath;

		f.open(fpath);
		if (f.is_open())
		{
			std::string skip;
			std::getline(f, skip);
			while (f.good())
				if (!read_manf(f)) break;
		}
		f.close();
	}
	catch (const std::string& strpath)
	{
		throw std::runtime_error(err_csv(strpath));
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << err_read(fpath) << std::endl << e.what() << std::endl;
		return false;
	}
	return true;
}

bool AppSystem::read_manf(std::ifstream& f)
{
	try
	{
		std::string sn, name, email;
		std::getline(f, sn, ',');
		std::getline(f, name, ',');
		std::getline(f, email);
		if (f.eof()) return true;
		manfs.push_back(new Manufacturer(sn.c_str(), name.c_str(), email));	
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << "Error reading manufacturer data." << std::endl <<
			e.what() << std::endl;
		return false;
	}
	return true;
}

template<>
bool AppSystem::import_data<App>(const char *fpath)
{
	std::ifstream f;
	f.exceptions(std::ifstream::badbit);
	try
	{
		std::string strpath(fpath);
		if (!valid_path(strpath)) throw strpath;

		f.open(fpath);
		if (f.is_open())
		{
			std::string skip;
			std::getline(f, skip);
			while (f.good())
			{
				std::string type;
				std::getline(f, type, ',');
				if (type == "Game")
					if (!read_game(f)) break;
				if (type == "Office")
					if (!read_office(f)) break;
			}
		}
		f.close();
	}
	catch (const std::string& strpath)
	{
		throw std::runtime_error(err_csv(strpath));
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << err_read(fpath) << std::endl << e.what() << std::endl;
		return false;
	}
	return true;
}

bool AppSystem::read_game(std::ifstream& f)
{
	try
	{
		std::string sn, name, os, manf, price, genre, online;
		std::string skip;
		std::getline(f, sn, ',');
		std::getline(f, name, ',');
		std::getline(f, os, ',');
		std::getline(f, manf, ',');
		std::getline(f, price, ',');
		std::getline(f, genre, ',');
		std::getline(f, online, ',');
		std::getline(f, skip);
		bool onl = online == "Yes";
		
		if (!manfs.empty())
		{
			for (auto& man : manfs)
			{
				if (man->get_name() == manf)
				{
					apps.push_back(new Game(sn.c_str(), name, os,
								man, std::stoi(price), genre, onl));
					break;
				}
			}
		}
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << "Error reading game data." << std::endl <<
			e.what() << std::endl;
		return false;
	}
	return true;
}

bool AppSystem::read_office(std::ifstream& f)
{
	try
	{
		std::string sn, name, os, manf, price, skip1, skip2;
		std::getline(f, sn, ',');
		std::getline(f, name, ',');
		std::getline(f, os, ',');
		std::getline(f, manf, ',');
		std::getline(f, price, ',');
		std::getline(f, skip1, ',');
		std::getline(f, skip2, ',');
		std::vector<std::string> exts =	read_office_exts(f);
		
		if (!manfs.empty())
		{
			for (auto& man : manfs)
			{
				if (man->get_name() == manf)
				{
					apps.push_back(new Office(sn.c_str(), name, os,
								man, std::stoi(price), exts));
					break;
				}
			}
		}
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << "Error reading office data." << std::endl <<
			e.what() << std::endl;
		return false;
	}
	return true;
}

const std::vector<std::string> AppSystem::read_office_exts(std::ifstream& f)
{
	std::vector<std::string> exts;
	std::string ext;
	std::getline(f, ext);
	std::istringstream iss(ext);	
	while (std::getline(iss, ext, '|'))	exts.push_back(ext);
	return exts;
}

template<>
bool AppSystem::import_data<Review>(const char *fpath)
{
	std::ifstream f;
	try
	{	
		std::string strpath(fpath);
		if (!valid_path(strpath)) throw strpath;
		f.open(fpath);
		std::string skip;
		std::getline(f, skip);
		while (f.good())
		{
			std::string appname, stars, username, comment;
			std::getline(f, appname, ',');
			std::getline(f, stars, ',');
			std::getline(f, username, ',');
			std::getline(f, comment);
			for (auto& app : apps)
				if (appname == app->get_name())
					app->addrev(new Review(std::stoi(stars), username, comment)); 
		}
	}
	catch (const std::string& strpath)
	{
		throw std::runtime_error(err_csv(strpath));
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << "Error reading reviews." << std::endl << e.what() << std::endl;
		return false;
	}
	return true;
}

template<>
bool AppSystem::export_data<Manufacturer>(const char *fpath)
{
	std::ofstream f;
	f.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		f.open(fpath);
		f << "SN,Name,Email\n";
		for (auto& manf : manfs)
			f << manf->get_serialnum() << ',' <<
				manf->get_name() << ',' <<
				manf->get_email() << std::endl;
		f.close();
	}
	catch (const std::ofstream::failure& e)
	{
		std::cerr << err_read(fpath) << std::endl << e.what() << std::endl;
		return false;
	}
	return true;
}

template<>
bool AppSystem::export_data<App>(const char *fpath)
{
	std::ofstream f;
	f.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		std::string strpath(fpath);
		if (!valid_path(strpath)) throw strpath;
		f.open(fpath);
		f << "Type,SN,Name,OS,Manf,Price,Genre,Online,Extensions\n";
		for (auto& app : apps)
		{
			Manufacturer manf = app->get_manf();
			Game *o = dynamic_cast<Game *>(app);
			f << (o ? "Game" : "Office") << ',';	
			f << app->get_serialnum() << ',' <<
				app->get_name() << ',' <<
				app->get_os() << ',' <<
				manf.get_name() << ',' <<
				app->get_price() << ',' <<
				(o ? o->get_genre() :"N/A") << ',' <<
				(o ? (o->get_online() ? "Yes" : "No") : "N/A") << ',';
			if (o) f << "N/A" << std::endl;
			else
			{
				Office *of = dynamic_cast<Office *>(app);
				write_office_exts(of, f);
				f << std::endl;
			}
		}
		f.close();
	}
	catch (const std::string& strpath)
	{
		throw std::runtime_error(err_csv(strpath));
	}
	catch (const std::ofstream::failure& e)
	{
		std::cerr << err_write(fpath) << e.what() << std::endl;
		return false;
	}
	return true;
}

template<>
bool AppSystem::export_data<Review>(const char *fpath)
{
	std::ofstream f;
	f.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		std::string strpath(fpath);
		if (!valid_path(strpath)) throw strpath;
		f.open(fpath);
		f << "AppName,Stars,Username,Comment\n";
		for (auto& app : apps)
		{
			const std::vector<Review *> revs = app->get_revs();
			if (!revs.empty())
				for (auto& rev : revs)
					f <<
						app->get_name() << ',' <<
						rev->get_stars() << ',' <<
						rev->get_username() << ',' <<
						rev->get_comment() << std::endl;	
		}
		f.close();
	}
	catch (const std::string& strpath)
	{
		throw std::runtime_error(err_csv(strpath));
	}
	catch (const std::ofstream::failure& e)
	{
		std::cerr << err_write(fpath) << e.what() << std::endl;
		return false;
	}
	return true;
}

void AppSystem::write_office_exts(Office *of, std::ofstream& f)
{
	std::vector<std::string> exts = of->get_exts();
	for (auto& ext : exts)
		f << ext << '|';	
}

void AppSystem::newrev(const std::string& appname, Review *rev)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			app->addrev(rev);
}

void AppSystem::newrevs(const std::string& appname, const std::vector<Review *> revs)
{
	for (auto& app : apps)
		if (app->get_name() == appname)
			app->addrevs(revs);
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
		if (Game *o = dynamic_cast<Game *>(app))
			if (o->get_name() == appname)
				o->set_genre(genre);
}

void AppSystem::chonline(const std::string& appname, bool online)
{
	for (auto& app : apps)
		if (Game *o = dynamic_cast<Game *>(app))
			if (o->get_name() == appname)
				o->set_online(online);
}

void AppSystem::chexts(const std::string& appname, const std::vector<std::string> exts)
{
	for (auto& app : apps)
		if (Office *o = dynamic_cast<Office *>(app))
			if (o->get_name() == appname)
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
			if (!revs.empty())
			{
				int sum = 0, count = 0;	
				for (auto& rev : revs)
				{
					sum += rev->get_stars();
					count++;
				}
				if (sum / count > 4) ggames.push_back(o);
			}
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

bool AppSystem::valid_path(const std::string& strpath)
{
	return (strpath.find(".csv") != std::string::npos);	
}

const std::string AppSystem::err_csv(const std::string& strpath)
{
	return "Error. File must be of format \'.csv\'. (" +
		strpath + ").";
}

const std::string AppSystem::err_read(const char *fpath)
{
	return "Error reading file \'" + std::string(fpath) + "\'.";
}

const std::string AppSystem::err_write(const char *fpath)
{
	return "Error writing to file (" + std::string(fpath) + ").";
}
