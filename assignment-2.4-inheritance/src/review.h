#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review
{
	private:
		int stars;
		std::string username;
		std::string comment;

	public:
		Review();
		Review(int stars, const std::string& username, const std::string& comment);

		int	get_stars() const;
		const std::string& get_username() const;
		const std::string& get_comment() const;

		void set_stars(int stars);
		void set_username(const std::string& username);
		void set_comment(const std::string& comment);
};

#endif /* REVIEW_H */
