#include "app.h"

App::App()
    :serialnum(nullptr), name(""), os(""), manf(nullptr), price(0) {}

App::App(const char *serialnum, const std::string& name,
    const std::string& os, Manufacturer *manf, int price)
    :serialnum(convsn(serialnum)), name(name), os(os), manf(manf), price(price)
{
    if (!std::strcmp(serialnum, ""))
        throw std::runtime_error("Empty app serial number.");   
    if (name.empty())
        throw std::runtime_error("Empty app name.");    
    if (os.empty())
        throw std::runtime_error("Empty OS name."); 
    if (price < 0)
        throw std::runtime_error("Price can't have negative value.");
}

App::App(const App& a)
    :serialnum(a.serialnum), name(a.name), os(a.os), manf(a.manf),
    price(a.price) {}

App::~App()
{
    if (serialnum != nullptr)
    {
        delete[] serialnum;
        serialnum = nullptr;    
    }
    if (!reviews.empty())
    {
        for (auto&& rev : reviews)
        {
            if (rev != nullptr)
            {
                delete rev;
                rev = nullptr;
            }
        }
        reviews.clear();
    }
}

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
