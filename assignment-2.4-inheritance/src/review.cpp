#include "review.h"

Review::Review()
    :stars(0), username(""), comment("") {}

Review::Review(int stars, const std::string& username, const std::string& comment)
    :stars(stars), username(username), comment(comment)
{
    if (stars < 0 || stars > 5)
        throw std::runtime_error("Wrong star value. Must be in [0, 5]");
}

Review::Review(const Review& rev)
    :stars(rev.stars), username(rev.username), comment(rev.comment) {}
