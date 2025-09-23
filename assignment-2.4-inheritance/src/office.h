#ifndef OFFICE_H
#define OFFICE_H

#include "app.h"

class Office: public App
{
	private:
		std::vector<std::string> extensions;

	public:
		Office();
		Office(const char *serialnum, const std::string& name,
				const std::string& os, Manufacturer *manf,
				int price, const std::vector<std::string>& ext);
		~Office();

		const std::vector<std::string>& get_exts() const;

		void set_exts(const std::vector<std::string>& extensions);
};

#endif /* OFFICE_H */
