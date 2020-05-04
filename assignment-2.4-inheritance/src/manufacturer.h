#ifndef MANUFACTURER_H
#define MANUFACTURER_H

#include <stdexcept>
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

		const char *get_serialnum() const;
		const char *get_name() const;
		const std::string& get_email() const;

		void set_serialnum(const char *serialnum);
		void set_name(const char *name);
		void set_email(const std::string& email);

	private:
		char *convstr(const char *str);
};

#endif /* MANUFACTURER_H */
