#ifndef APP_HPP
#define APP_HPP

#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "errlog.hpp"
#include "manufacturer.hpp"
#include "review.hpp"

class App
{
    protected:
        const char *serialnum;
        std::string name;
        std::string os;
        Manufacturer *manf;
        std::vector<Review *> reviews;
        int price;
        ErrLog errlog;

    public:
        App();
        App(const char *serialnum, const std::string& name,
            const std::string& os, Manufacturer *manf, int price);
        App(const App& app);
        virtual ~App(); 

        void addrev(Review *rev) {reviews.push_back(rev);}
        void addrevs(const std::vector<Review *> revs)
            {reviews.insert(reviews.end(), revs.begin(), revs.end());}

        const std::string& get_name() const {return name;}
        const std::string& get_os()   const {return os;}
        constexpr const Manufacturer& get_manf() const {return *manf;}
        constexpr const char *get_serialnum() const {return serialnum;}
        constexpr const std::vector<Review *>& get_revs() const {return reviews;}
        constexpr const int get_price() const {return price;}

        void set_serialnum(const char *serialnum);
        void set_name(const std::string& name) {this->name = name;}
        void set_os(const std::string& os)     {this->os = os;}
        void set_manf(Manufacturer *manf)      {this->manf = manf;}
        void set_price(const int price)        {this->price = price;}

        virtual void print(std::ostream& stream) const = 0;
    
    private:
        char *convsn(const char *serialnum);
};

#endif /* APP_HPP */
