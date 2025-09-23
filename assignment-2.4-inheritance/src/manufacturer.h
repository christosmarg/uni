#ifndef MANUFACTURER_H
#define MANUFACTURER_H

#include <string>
#include <string.h>

class Manufacturer
{
	private:
		const char *serialnum;
		const char *name;
		std::string email;

	public:
		Manufacturer();
		Manufacturer(const char *serialnum, const char *name,
				const std::string& email);
		Manufacturer(const Manufacturer& m);
		~Manufacturer();

		char *convstr(const char *str);

		const char *get_serialnum() const;
		const char *get_name() const;
		const std::string& get_email() const;
};

#endif /* MANUFACTURER_H */
