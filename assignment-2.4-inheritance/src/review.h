#ifndef REVIEW_H
#define REVIEW_H

#include <stdexcept>
#include <string>

class Review
{
    private:
        int stars;
        std::string username;
        std::string comment;

    public:
        Review();
        Review(int stars, const std::string& username,
               const std::string& comment);
        Review(const Review& rev);

        const std::string& get_username() const {return username;}
        const std::string& get_comment()  const {return comment;}
        constexpr const int get_stars()   const {return stars;}

        void set_stars(const int stars) {this->stars = stars;}
        void set_username(const std::string& username)
            {this->username = username;}
        void set_comment(const std::string& comment)
            {this->comment = comment;}
};

#endif /* REVIEW_H */
