#include "office.h"

Office::Office()
	:App() {}

Office::Office(const char *serialnum, const std::string& name,
		const std::string& os, Manufacturer *manf,
		int price, const std::vector<std::string>& ext)
	:App(serialnum, name, os, manf, price), extensions(ext) {}

const std::vector<std::string>& Office::get_exts() const
{
	return extensions;
}
