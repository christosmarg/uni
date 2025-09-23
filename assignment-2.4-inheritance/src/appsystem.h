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
		const std::vector<Manufacturer *>&	get_manfs() const;

	private:
		bool read_manf(std::ifstream& f);
		bool read_game(std::ifstream& f);
		bool read_office(std::ifstream& f);
		const std::vector<std::string> read_office_exts(std::ifstream& f);
		const std::vector<Review *>
			read_reviews(const std::string& appname, const char *rpath);
		void write_office_exts(Office *of, std::ofstream& f);
		bool valid_path(const std::string& strpath);
		const std::string err_csv(const std::string& fpath);
		const std::string err_read(const char *fpath);
		const std::string err_write(const char *fpath);
};

#endif /* APPSYSTEM_H */
