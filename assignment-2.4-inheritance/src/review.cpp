#include "review.h"

Review::Review()
	:stars(0), username(""), comment("") {}

Review::Review(int stars, const std::string& username, const std::string& comment)
	:stars(stars), username(username), comment(comment)
{
	if (stars < 0 || stars > 5)
		throw std::runtime_error("Wrong star value. Must be in [0, 5]");
}

Review::Review(const Review& r)
	:stars(r.stars), username(r.username), comment(r.comment) {}

const std::string&
Review::get_username() const
{
	return username;
}

const std::string&
Review::get_comment() const
{
	return comment;
}

void
Review::set_stars(int stars)
{
	this->stars = stars;
}

void
Review::set_username(const std::string& username)
{
	this->username = username;
}

void
Review::set_comment(const std::string& comment)
{
	this->comment = comment;
}
