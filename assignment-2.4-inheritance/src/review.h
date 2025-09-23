#ifndef REVIEW_H
#define REVIEW_H

#include "appsystem.h"

class Review : public AppSystem
{
	private:
		int stars;
		std::string username;
		std::string comment;

	public:
		Review();
		virtual ~Review();
};

#endif /* REVIEW_H */
