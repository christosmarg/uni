#ifndef OFFICE_H
#define OFFICE_H

#include "manufacturer.h"
#include "review.h"

class Office : public Manufacturer, public Review
{
	private:
		std::vector<std::string> extensions;
		std::string os;
		int price;

	public:
		Office();
		~Office();
};

#endif /* OFFICE_H */
