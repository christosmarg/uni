#include "review.h"

Review::Review()
	:stars(0), username(""), comment("") {}

Review::Review(int stars, const std::string& username, const std::string& comment)
	:stars(stars), username(username), comment(comment) {}

int Review::get_stars() const
{
	return stars;
}

const std::string& Review::get_username() const
{
	return username;
}

const std::string& Review::get_comment() const
{
	return comment;
}
