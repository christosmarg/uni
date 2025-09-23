#ifndef APPSYSTEM_H
#define APPSYSTEM_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "game.h"
#include "office.h"

class AppSystem
{
	private:
		std::vector<App *> apps;
		std::vector<Manufacturer *> manfs;

	public:
		AppSystem();
		~AppSystem();

		AppSystem& operator+= (App *app);
		AppSystem& operator+= (Manufacturer *manf);

		template<typename T> bool import_data(const char *fpath);
		template<typename T> bool export_data(const char *fpath);
		void newrev		(const std::string& appname, Review *rev);
		void newrevs	(const std::string& appname, const std::vector<Review *> revs);
		void chserialnum(const std::string& appname, const char *serialnum);
		void chname		(const std::string& appname, const std::string& name);
		void chos		(const std::string& appname, const std::string& os);
		void chmanf		(const std::string& appname, Manufacturer *manf);
		void chprice	(const std::string& appname, int price);
		void chgenre	(const std::string& appname, const std::string& genre);
		void chonline	(const std::string& appname, bool online);
		void chexts		(const std::string& appname, const std::vector<std::string> exts);
		void removebad	(Manufacturer *man);
		void removebad	(const char *manfname);
		
		const std::vector<Office *> get_freeapps() const;
		const std::vector<Game *> get_goodgames() const;
		const std::vector<App *>& get_apps() const;
		const std::vector<Manufacturer *>& get_manfs() const;

	private:
		template<typename T> bool parse(std::ifstream& f);
		const std::vector<std::string> parse_office_exts(std::ifstream& f);
		const std::vector<Review *>
			parse_reviews(const std::string& appname, const char *rpath);
		void write_office_exts(Office *of, std::ofstream& f);
		bool valid_path(const std::string& strpath);
		const std::string err_csv(const std::string& fpath);
		const std::string err_read(const char *fpath);
		const std::string err_write(const char *fpath);
		template<typename T> void dealloc(std::vector<T *>& vec);
};

template<typename T> bool
AppSystem::parse(std::ifstream& f)
{
	try
	{
		if (std::is_same<T, Manufacturer>::value)
		{
			std::string sn, name, email;
			std::getline(f, sn, ',');
			std::getline(f, name, ',');
			std::getline(f, email);
			if (f.eof()) return true;
			manfs.push_back(new Manufacturer(sn.c_str(), name.c_str(), email));	
		}	
		else if (std::is_same<T, Office>::value)
		{
			std::string sn, name, os, manf, price, skip1, skip2;
			std::getline(f, sn, ',');
			std::getline(f, name, ',');
			std::getline(f, os, ',');
			std::getline(f, manf, ',');
			std::getline(f, price, ',');
			std::getline(f, skip1, ',');
			std::getline(f, skip2, ',');
			if (f.eof()) return true;
			std::vector<std::string> exts =	parse_office_exts(f);
			
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
		else if (std::is_same<T, Game>::value)
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
			if (f.eof()) return true;
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
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << "Error parsing data." << std::endl <<
			e.what() << std::endl;
		return false;
	}
	return true;
}

template<typename T> bool
AppSystem::import_data(const char *fpath)
{
	std::ifstream f;
	f.exceptions(std::ifstream::badbit);
	try
	{
		std::string strpath(fpath);
		if (!valid_path(strpath))
			throw std::runtime_error(err_csv(strpath));
		f.open(fpath);
		if (f.is_open())
		{
			std::string skip;
			std::getline(f, skip);
			while (f.good())
			{
				if (std::is_same<T, Manufacturer>::value)
				{
					if (!parse<Manufacturer>(f)) break;
				}
				else if (std::is_same<T, App>::value)
				{
					std::string type;
					std::getline(f, type, ',');
					if (type == "Game")
						if (!parse<Game>(f)) break;
					if (type == "Office")
						if (!parse<Office>(f)) break;
				}
				else if (std::is_same<T, Review>::value)
				{
					std::string appname, stars, username, comment;
					std::getline(f, appname, ',');
					std::getline(f, stars, ',');
					std::getline(f, username, ',');
					std::getline(f, comment);
					if (f.eof()) return true;
					for (auto& app : apps)
						if (appname == app->get_name())
							app->addrev(new Review(std::stoi(stars), username, comment)); 
				}
			}
		}
		f.close();
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << err_read(fpath) << std::endl << e.what() << std::endl;
		return false;
	}
	return true;
}

template<typename T> bool
AppSystem::export_data(const char *fpath)
{
	std::ofstream f;
	f.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		std::string strpath(fpath);
		if (!valid_path(strpath))
			throw std::runtime_error(err_csv(strpath));
		f.open(fpath);

		if (std::is_same<T, Manufacturer>::value)
		{
			f << "SN,Name,Email\n";
			for (auto& manf : manfs)
				f << manf->get_serialnum() << ',' <<
					manf->get_name() << ',' <<
					manf->get_email() << std::endl;
		}
		else if (std::is_same<T, App>::value)
		{
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
		}
		else if (std::is_same<T, Review>::value)
		{
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
		}
		f.close();
	}
	catch (const std::ofstream::failure& e)
	{
		std::cerr << err_read(fpath) << std::endl << e.what() << std::endl;
		return false;
	}
	return true;
}

template<typename T> void
AppSystem::dealloc(std::vector<T *>& vec)
{
	for (auto& v : vec)
		if (v != nullptr)
			delete v;
	if (!vec.empty())
		vec.clear();
}

#endif /* APPSYSTEM_H */
