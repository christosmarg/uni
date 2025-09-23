#ifndef MANUFACTURER_H
#define MANUFACTURER_H

#include <cstring>
#include <stdexcept>
#include <string>

class Manufacturer
{
    private:
        const char *serialnum;
        const char *name;
        std::string email;

    public:
        Manufacturer();
        Manufacturer(const char *serialnum, const char *name,
                     const std::string& email);
        Manufacturer(const Manufacturer& m);
        ~Manufacturer();

        const std::string& get_email()        const {return email;}
        constexpr const char *get_serialnum() const {return serialnum;}
        constexpr const char *get_name()      const {return name;}

        void set_serialnum(const char *serialnum);
        void set_name(const char *name); 
        void set_email(const std::string& email) {this->email = email;}

    private:
        char *convstr(const char *str);
};

#endif /* MANUFACTURER_H */
