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
        AppSystem() = default;
        ~AppSystem();

        AppSystem& operator+= (App *app);
        AppSystem& operator+= (Manufacturer *manf);

        template<typename T> bool import_data(const char *fpath);
        template<typename T> bool export_data(const char *fpath);
        template<typename T> void call(
                const std::string& appname,
                const T element,
                void (App::*func)(T));
        template<typename T, class U> void cast_call(
                const std::string& appname,
                const T element,
                void (U::*func)(T));
        void removebad(const Manufacturer *manf);
        void removebad(const char *manfname);
        
        constexpr const std::vector<App *>& get_apps() const {return apps;}
        constexpr const std::vector<Manufacturer *>& get_manfs() const {return manfs;} 
        const std::vector<Office *> get_freeapps() const;
        const std::vector<Game *> get_goodgames() const;

    private:
        template<typename T> bool exists(const std::vector<T *>& vec, const T *element);
        template<typename T> bool parse(std::ifstream& f);
        const std::vector<std::string> parse_office_exts(std::ifstream& f);
        const std::vector<Review *>
            parse_reviews(const std::string& appname, const char *rpath);
        void write_office_exts(const Office *of, std::ofstream& f);
        bool valid_path(const std::string& strpath);
        const std::string err_csv(const std::string& strpath);
        const std::string err_read(const std::string& strpath);
        const std::string err_write(const std::string& strpath);
        template<typename T> void dealloc(std::vector<T *>& vec);
};

template<typename T> bool
AppSystem::parse(std::ifstream& f)
{
    try
    {
        if constexpr (std::is_same_v<T, Manufacturer>)
        {
            std::string sn, name, email;
            std::getline(f, sn, ',');
            std::getline(f, name, ',');
            std::getline(f, email);
            if (f.eof()) return true;
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
            if (f.eof()) return true;
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
            if (f.eof()) return true;
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
            std::printf("Importing data from \'%s\'\n", fpath);
            std::string skip;
            std::getline(f, skip);
            while (f.good())
            {
                if constexpr (std::is_same_v<T, Manufacturer>)
                {
                    if (!parse<Manufacturer>(f)) break;
                }
                else if constexpr (std::is_same_v<T, App>)
                {
                    std::string type;
                    std::getline(f, type, ',');
                    if (type == "Game")
                        if (!parse<Game>(f)) break;
                    if (type == "Office")
                        if (!parse<Office>(f)) break;
                }
                else if constexpr (std::is_same_v<T, Review>)
                {
                    std::string appname, stars, username, comment;
                    std::getline(f, appname, ',');
                    std::getline(f, stars, ',');
                    std::getline(f, username, ',');
                    std::getline(f, comment);
                    if (f.eof()) return true;
                    for (auto&& app : apps)
                        if (appname == app->get_name())
                            app->addrev(new Review(std::stoi(stars), username, comment)); 
                }
            }
        }
        f.close();
    }
    catch (const std::ifstream::failure& e)
    {
        std::cerr << err_read(std::string(fpath)) << std::endl << e.what() << std::endl;
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
        std::cerr << err_write(std::string(fpath)) << std::endl << e.what() << std::endl;
        return false;
    }
    return true;
}

template<typename T> bool
AppSystem::exists(const std::vector<T *>& vec, const T *element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

template<typename T> void
AppSystem::call(const std::string& appname, const T element, void (App::*func)(T))
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            (app->*func)(element);
}

template<typename T, class U> void
AppSystem::cast_call(const std::string& appname, const T element, void (U::*func)(T))
{
    for (auto&& app : apps)
        if (U *o = dynamic_cast<U *>(app))
            if (o->get_name() == appname)
                (o->*func)(element);
}

template<typename T> void
AppSystem::dealloc(std::vector<T *>& vec)
{
    if (!vec.empty())
    {
        for (auto&& v : vec)
        {
            if (v != nullptr)
            {
                delete v;
                v = nullptr;    
            }
        }
        vec.clear();
    }
}

#endif /* APPSYSTEM_H */
