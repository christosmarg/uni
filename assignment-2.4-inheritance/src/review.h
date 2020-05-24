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
		Review(const Review& r);

		inline const std::string& get_username() const {return username;}
		inline const std::string& get_comment()  const {return comment;}
		inline constexpr int get_stars()		 const {return stars;}

		inline void set_stars(int stars) {this->stars = stars;}
		inline void set_username(const std::string& username)
			{this->username = username;}
		inline void set_comment(const std::string& comment)
			{this->comment = comment;}
};

#endif /* REVIEW_H */
