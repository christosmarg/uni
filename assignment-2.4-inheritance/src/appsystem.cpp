#include "appsystem.hpp"

AppSystem::AppSystem() {errlog.fclear();}

AppSystem::~AppSystem()
{
    dealloc<App>(apps);
    dealloc<Manufacturer>(manfs);
}

/* 
 * Adds a new App object to the apps vector in case it doesn't already exist.
 * If it exists, an error is written to the error log.
 */
AppSystem&
AppSystem::operator+= (App *app)
{
    if (!exists<App>(apps, app)) apps.push_back(app);
    else errlog.write("App: " + std::string(app->get_serialnum()) +
            ": exists already");
    return *this;
}

/* Same as above, but for a Manufacturer object */
AppSystem&
AppSystem::operator+= (Manufacturer *manf)
{
    if (!exists<Manufacturer>(manfs, manf)) manfs.push_back(manf);
    else errlog.write("Manufacturer: " + std::string(manf->get_serialnum()) +
            ": exists already");
    return *this;
}

/* 
 * Parses a given file containing file extensions for an Office object
 * which are formatted as: .ext1|.ext2|.
 * Using STL's sstream we can extract each extension as a substring
 * by setting the delimeter to | and then push them back to
 * a vector which contains each extension.
 */
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

/* Writes file extensions to a file with the above format */
void
AppSystem::write_office_exts(const Office *of, std::ofstream& f)
{
    std::vector<std::string> exts = of->get_exts();
    for (const auto& ext : exts)
        f << ext << '|';    
}

/* 
 * Searches through the apps vector to see if a given Manufacturer
 * object exists. If it does, it deletes every single app related
 * to that manufacturer.
 */
void
AppSystem::removebad(const Manufacturer *manf)
{
    auto lambda = [&](App *app) -> bool
    {
        Manufacturer m = app->get_manf();
        if (!std::strcmp(m.get_serialnum(), manf->get_serialnum()))
            delete app;
        return !std::strcmp(m.get_serialnum(), manf->get_serialnum());
    };
    apps.erase(std::remove_if(apps.begin(), apps.end(), lambda), apps.end());
}

/* 
 * Same as above but this time we only pass the
 * manufacturer's serial number
 */
void
AppSystem::removebad(const char *manfsn)
{
    auto lambda = [&](App *app) -> bool
    {
        Manufacturer m = app->get_manf();
        if (!std::strcmp(m.get_serialnum(), manfsn))
            delete app;
        return !std::strcmp(m.get_serialnum(), manfsn);
    };
    apps.erase(std::remove_if(apps.begin(), apps.end(), lambda), apps.end());
}

/* 
 * Returns a vector of Office objects whose prices are 0 (free).
 * dynamic_cast is required in order to only take Office objects
 * into account (the vector contains App objects).
 */
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

/* 
 * Returns a vector with all the Game objects that have an
 * average rating bigger than 4. dynamic_cast is required
 * for the same reason as above.
 */
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

const std::string
AppSystem::err_read(const char *fpath)
{
    return "Error reading file \'" + std::string(fpath) + "\'.";
}

const std::string
AppSystem::err_write(const char *fpath)
{
    return "Error writing to file \'" + std::string(fpath) + "\'.";
}
