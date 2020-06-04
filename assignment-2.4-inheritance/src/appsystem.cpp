#include "appsystem.h"

AppSystem::~AppSystem()
{
    dealloc<App>(apps);
    dealloc<Manufacturer>(manfs);
}

AppSystem&
AppSystem::operator+= (App *app)
{
    if (!exists<App>(apps, app)) apps.push_back(app);
    else throw std::logic_error("App exists already.");
    return *this;
}

AppSystem&
AppSystem::operator+= (Manufacturer *manf)
{
    if (!exists<Manufacturer>(manfs, manf)) manfs.push_back(manf);
    else throw std::logic_error("Manufacturer exists already.");
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
AppSystem::write_office_exts(const Office *of, std::ofstream& f)
{
    std::vector<std::string> exts = of->get_exts();
    for (const auto& ext : exts)
        f << ext << '|';    
}

void
AppSystem::removebad(const Manufacturer *manf)
{
    auto lambda = [&](App *app) -> bool
    {
        Manufacturer m = app->get_manf();
        if (!std::strcmp(m.get_name(), manf->get_name()))
            delete app;
        return !std::strcmp(m.get_name(), manf->get_name());
    };
    apps.erase(std::remove_if(apps.begin(), apps.end(), lambda), apps.end());
}

void
AppSystem::removebad(const char *manfname)
{
    auto lambda = [&](App *app) -> bool
    {
        Manufacturer m = app->get_manf();
        if (!std::strcmp(m.get_name(), manfname))
            delete app;
        return !std::strcmp(m.get_name(), manfname);
    };
    apps.erase(std::remove_if(apps.begin(), apps.end(), lambda), apps.end());
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
