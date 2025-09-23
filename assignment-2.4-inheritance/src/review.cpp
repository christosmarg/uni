#include "review.hpp"

Review::Review()
    :stars(0), username(""), comment("") {}

Review::Review(int stars, const std::string& username, const std::string& comment)
    :stars(stars), username(username), comment(comment)
{
    if (stars < 0 || stars > 5)
        errlog.write("Review from: " + username + ": Star value out of bounds");
}

Review::Review(const Review& rev)
    :stars(rev.stars), username(rev.username), comment(rev.comment) {}
