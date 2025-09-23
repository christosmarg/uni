#ifndef APPSYSTEM_H
#define APPSYSTEM_H

#include <algorithm>
#include <fstream>
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

		bool read_data(const char *fpath);
		bool export_data(const char *fpath);
		void newrev(const std::string& appname, Review *rev);
		void chserialnum(const std::string& appname, const char *serialnum);
		void chname(const std::string& appname, const std::string& name);
		void chos(const std::string& appname, const std::string& os);
		void chmanf(const std::string& appname, Manufacturer *manf);
		void chprice(const std::string& appname, int price);
		void removebad(Manufacturer *man);
		
		const std::vector<App *>& get_apps() const;
		const std::vector<Manufacturer *>& get_manfs() const;
};

#endif /* APPSYSTEM_H */
