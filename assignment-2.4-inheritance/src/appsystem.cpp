#include "appsystem.h"

AppSystem::AppSystem() {} 

AppSystem::~AppSystem()
{
    dealloc<App>(apps);
    dealloc<Manufacturer>(manfs);
}

AppSystem&
AppSystem::operator+= (App *app)
{
    apps.push_back(app);
    return *this;
}

AppSystem&
AppSystem::operator+= (Manufacturer *man)
{
    manfs.push_back(man);
    return *this;
}

const std::vector<std::string>
AppSystem::parse_office_exts(std::ifstream& f)
{
    std::vector<std::string> exts;
    std::string ext;
    std::getline(f, ext);
    std::istringstream iss(ext);    
    while (std::getline(iss, ext, '|')) exts.push_back(ext);
    return exts;
}

void
AppSystem::write_office_exts(Office *of, std::ofstream& f)
{
    std::vector<std::string> exts = of->get_exts();
    for (const auto& ext : exts)
        f << ext << '|';    
}

void
AppSystem::newrev(const std::string& appname, Review *rev)
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            app->addrev(rev);
}

void
AppSystem::newrevs(const std::string& appname, const std::vector<Review *> revs)
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            app->addrevs(revs);
}

void
AppSystem::chserialnum(const std::string& appname, const char *serialnum)
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            app->set_serialnum(serialnum);
}

void
AppSystem::chname(const std::string& appname, const std::string& name)
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            app->set_name(name);
}

void
AppSystem::chos(const std::string& appname, const std::string& os)
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            app->set_os(os);
}

void
AppSystem::chmanf(const std::string& appname, Manufacturer *manf)
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            app->set_manf(manf);
}

void
AppSystem::chprice(const std::string& appname, int price)
{
    for (auto&& app : apps)
        if (app->get_name() == appname)
            app->set_price(price);
}

void
AppSystem::chgenre(const std::string& appname, const std::string& genre)
{
    for (const auto& app : apps)
        if (Game *o = dynamic_cast<Game *>(app))
            if (o->get_name() == appname)
                o->set_genre(genre);
}

void
AppSystem::chonline(const std::string& appname, bool online)
{
    for (const auto& app : apps)
        if (Game *o = dynamic_cast<Game *>(app))
            if (o->get_name() == appname)
                o->set_online(online);
}

void
AppSystem::chexts(const std::string& appname, const std::vector<std::string> exts)
{
    for (const auto& app : apps)
        if (Office *o = dynamic_cast<Office *>(app))
            if (o->get_name() == appname)
                o->set_exts(exts);
}

void
AppSystem::removebad(Manufacturer *man)
{
    apps.erase(std::remove_if(apps.begin(), apps.end(), [&](App *app)
        {
            Manufacturer m = app->get_manf();
            if (!std::strcmp(m.get_name(), man->get_name()))
                delete app;
            return !std::strcmp(m.get_name(), man->get_name());
        }), apps.end());    
}

void
AppSystem::removebad(const char *manfname)
{
    apps.erase(std::remove_if(apps.begin(), apps.end(), [&](App *app)
        {
            Manufacturer m = app->get_manf();
            if (!std::strcmp(m.get_name(), manfname))
                delete app;
            return !std::strcmp(m.get_name(), manfname);
        }), apps.end());    
}

const std::vector<Office *>
AppSystem::get_freeapps() const
{
    std::vector<Office *> fapps;
    for (const auto& app : apps)
        if (Office *o = dynamic_cast<Office *>(app))
            if (o->get_price() == 0)
                fapps.push_back(o);
    return fapps;
}

const std::vector<Game *>
AppSystem::get_goodgames() const
{
    std::vector<Game *> ggames;
    for (const auto& app : apps)
    {
        if (Game *o = dynamic_cast<Game *>(app))
        {
            std::vector<Review *> revs = o->get_revs();
            if (!revs.empty())
            {
                int sum = 0, count = 0; 
                for (const auto& rev : revs)
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

bool
AppSystem::valid_path(const std::string& strpath)
{
    return (strpath.find(".csv") != std::string::npos); 
}

const std::string
AppSystem::err_csv(const std::string& strpath)
{
    return "Error. File must be of format \'.csv\'. (" + strpath + ").";
}

const std::string
AppSystem::err_read(const std::string& strpath)
{
    return "Error reading file \'" + strpath + "\'.";
}

const std::string
AppSystem::err_write(const std::string& strpath)
{
    return "Error writing to file \'" + strpath + "\'.";
}
