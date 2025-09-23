#include "review.hpp"

Review::Review()
    :stars(0), username(""), comment("") {}

Review::Review(const int stars, const std::string& username,
        const std::string& comment)
    :stars(stars), username(username), comment(comment)
{
    if (username.empty())
        errlog.write("Missing username");
    if (comment.empty())
        errlog.write("Missing comment");
    if (stars < 0 || stars > 5)
        errlog.write("Review from: " + username + ": Star value out of bounds");
}
