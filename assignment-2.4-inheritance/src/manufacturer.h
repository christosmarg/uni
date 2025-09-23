#ifndef MANUFACTURER_H
#define MANUFACTURER_H

#include "appsystem.h"

class Manufacturer : public AppSystem
{
	private:
		const char *serialnum;
		const char *name;
		std::string email;

	public:
		Manufacturer();
		virtual ~Manufacturer();
};

#endif /* MANUFACTURER_H */
