#ifndef APPSYSTEM_H
#define APPSYSTEM_H

#include <algorithm>
#include <fstream>
#include <iostream>
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

		bool read_data	(const char *fpath);
		bool export_data(const char *fpath);
		void newrev		(const std::string& appname, Review *rev);
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
		const std::vector<Manufacturer *>&	get_manfs() const;
};

#endif /* APPSYSTEM_H */
