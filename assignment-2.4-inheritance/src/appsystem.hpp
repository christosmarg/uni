#ifndef APPSYSTEM_HPP
#define APPSYSTEM_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "errlog.hpp"
#include "game.hpp"
#include "office.hpp"

class AppSystem
{
    private:
        std::vector<App *> apps;
        std::vector<Manufacturer *> manfs;
        ErrLog errlog;

    public:
        AppSystem();
        ~AppSystem();

        AppSystem& operator+= (App *app);
        AppSystem& operator+= (Manufacturer *manf);

        template<typename T> void import_data(const char *fpath);
        template<typename T> void export_data(const char *fpath);
        template<typename T> void call(
                std::string&& appname,
                const T element,
                void (App::*setter)(T));
        template<typename T, class U> void cast_call(
                std::string&& appname,
                const T element,
                void (U::*setter)(T));
        void removebad(const Manufacturer *manf);
        void removebad(const char *manfsn);
        
        constexpr const std::vector<App *>& get_apps() const {return apps;}
        constexpr const std::vector<Manufacturer *>& get_manfs() const {return manfs;} 
        const std::vector<Office *> get_freeapps() const;
        const std::vector<Game *> get_goodgames() const;

    private:
        template<typename T> bool exists(const std::vector<T *>& vec, const T *element);
        template<typename T> void parse(std::ifstream& f);
        const std::vector<std::string> parse_office_exts(std::ifstream& f);
        const std::vector<Review *>
            parse_reviews(const std::string& appname, const char *rpath);
        void write_office_exts(const Office *of, std::ofstream& f);
        const std::string err_read(const char *fpath);
        const std::string err_write(const char *fpath);
        template<typename T> void dealloc(std::vector<T *>& vec);
};

/* 
 * Parses .csv fields for each type T
 * The function is templated just for the sake
 * of not having overloads, although this one is
 * not any more practical either.
 */ 
template<typename T> void
AppSystem::parse(std::ifstream& f)
{
	if constexpr (std::is_same_v<T, Manufacturer>)
	{
		std::string sn, name, email;
		std::getline(f, sn, ',');
		std::getline(f, name, ',');
		std::getline(f, email);
		if (f.eof()) return;
		manfs.push_back(new Manufacturer(sn.c_str(), name.c_str(), email)); 
	}   
	else if constexpr (std::is_same_v<T, Office>)
	{
		std::string sn, name, os, manf, price, skip1, skip2;
		std::getline(f, sn, ',');
		std::getline(f, name, ',');
		std::getline(f, os, ',');
		std::getline(f, manf, ',');
		std::getline(f, price, ',');
		std::getline(f, skip1, ',');
		std::getline(f, skip2, ',');
		if (f.eof()) return;
		std::vector<std::string> exts = parse_office_exts(f);
		
		if (!manfs.empty())
		{
			for (const auto& man : manfs)
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
	else if constexpr (std::is_same_v<T, Game>)
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
		if (f.eof()) return;
		bool onl = online == "Yes";
		
		if (!manfs.empty())
		{
			for (const auto& man : manfs)
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
	else if constexpr (std::is_same_v<T, Review>)
	{
		std::string appname, stars, username, comment;
		std::getline(f, appname, ',');
		std::getline(f, stars, ',');
		std::getline(f, username, ',');
		std::getline(f, comment);
		if (f.eof()) return;
		for (auto&& app : apps)
			if (appname == app->get_name())
				app->addrev(new Review(std::stoi(stars), username, comment)); 
	}
}

/* 
 * Imports data from a given path and handles a possible
 * std::ifstream::badbit exception
 */
template<typename T> void
AppSystem::import_data(const char *fpath)
{
    std::ifstream f;
    f.exceptions(std::ifstream::badbit);
    try
    {
        std::string strpath(fpath);
        f.open(fpath);
        if (f.is_open())
        {
            std::printf("Importing data from \'%s\'\n", fpath);
            std::string skip;
            std::getline(f, skip);
            while (f.good())
            {
                if constexpr (std::is_same_v<T, Manufacturer>)
                    parse<Manufacturer>(f);
                else if constexpr (std::is_same_v<T, App>)
                {
                    std::string type;
                    std::getline(f, type, ',');
                    if (type == "Game") parse<Game>(f);
                    if (type == "Office") parse<Office>(f);
                }
                else if constexpr (std::is_same_v<T, Review>)
					parse<Review>(f);
            }
        }
        f.close();
    }
    catch (const std::ifstream::failure& e)
    {
        /*
         * We terminate because there's no point in continuing if
         * the file is corrupted
         */
        throw std::runtime_error(err_read(fpath) + " (" + e.what() + ")");
    }
}

/* 
 * Exports data to a given path for each type T.
 * This function is also templated just for the sake
 * of not having overloads. It also handles exceptions.
 */
template<typename T> void
AppSystem::export_data(const char *fpath)
{
    std::ofstream f;
    f.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try
    {
        std::string strpath(fpath);
        f.open(fpath);
        std::printf("Exporting data to \'%s\'\n", fpath);
        
        if constexpr (std::is_same_v<T, Manufacturer>)
        {
            f << "SN,Name,Email\n";
            for (const auto& manf : manfs)
                f << manf->get_serialnum() << ',' <<
                    manf->get_name() << ',' <<
                    manf->get_email() << std::endl;
        }
        else if constexpr (std::is_same_v<T, App>)
        {
            f << "Type,SN,Name,OS,Manf,Price,Genre,Online,Extensions\n";
            for (const auto& app : apps)
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
        else if constexpr (std::is_same_v<T, Review>)
        {
            f << "AppName,Stars,Username,Comment\n";
            for (const auto& app : apps)
            {
                const std::vector<Review *> revs = app->get_revs();
                if (!revs.empty())
                    for (const auto& rev : revs)
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
        /*
         * In this case we don't terminate because the output
         * file is not to be used by the program later, so
         * we shouldn't lose all progress.
         */
        errlog.write(err_write(fpath) + " (" + e.what() + ")");
    }
}

/* 
 * Searches a vector of any type T and returns true if the
 * element is found. I made it just so I don't have to write
 * all this every time.
 */
template<typename T> bool
AppSystem::exists(const std::vector<T *>& vec, const T *element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

/* 
 * Searches through the apps array and in case the app is found
 * it calls a given App setter through a function pointer.
 * "element" must be of the same type as the setter's parameter.
 * It's ugly.
 */
template<typename T> void
AppSystem::call(std::string&& appname, const T element, void (App::*setter)(T))
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            (app->*setter)(element);
}

/* 
 * Same as above but this one is used for the derived classes
 * "Game" and "Office". I could use this one in all cases but
 * dynamic casting everytime would be pointless.
 */
template<typename T, class U> void
AppSystem::cast_call(std::string&& appname, const T element, void (U::*setter)(T))
{
    for (auto&& app : apps)
        if (U *o = dynamic_cast<U *>(app))
            if (o->get_name() == appname)
                (o->*setter)(element);
}

/* 
 * Frees every pointer object in every vector.
 * This function is called only by the destructor.
 */
template<typename T> void
AppSystem::dealloc(std::vector<T *>& vec)
{
    if (!vec.empty())
    {
        for (auto&& v : vec)
            if (v != nullptr)
                delete v;
        vec.clear();
    }
}

#endif /* APPSYSTEM_HPP */
