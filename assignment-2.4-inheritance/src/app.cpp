#include "app.hpp"

App::App()
    :serialnum(nullptr), name(""), os(""), manf(nullptr), price(0) {}

App::App(const char *serialnum, const std::string& name,
    const std::string& os, Manufacturer *manf, const int price)
    :serialnum(convsn(serialnum)), name(name), os(os), manf(manf), price(price)
{
    if (!std::strcmp(serialnum, ""))
        errlog.write("Missing app serial number");
    if (name.empty())
        errlog.write("App: " + std::string(serialnum) + ": Missing app name");
    if (os.empty())
        errlog.write("App: " + std::string(serialnum) + ": Missing OS version");
    if (price < 0)
        errlog.write("App: " + std::string(serialnum) + ": Negative price");
}

App::App(const App& app)
    :serialnum(convsn(app.serialnum)), name(app.name), os(app.os), manf(app.manf),
    price(app.price) {}

App::~App()
{
    if (serialnum != nullptr) delete[] serialnum;
    if (!reviews.empty())
    {
        for (auto&& rev : reviews)
            if (rev != nullptr)
                delete rev;
        reviews.clear();
    }
}

/* 
 * Makes a copy of a const char array and returns
 * a temporary array which is meant to be stored in
 * a member variable.
 */
char *
App::convsn(const char *serialnum)
{
    int len = std::strlen(serialnum);
    char *tmp = new char[len + 1];
    std::copy(serialnum, serialnum + len + 1, tmp);
    return tmp; 
}

void
App::set_serialnum(const char *serialnum)
{
    if (this->serialnum != nullptr) delete[] this->serialnum;
    this->serialnum = convsn(serialnum);
}
