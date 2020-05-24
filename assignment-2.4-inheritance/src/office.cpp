#include "office.h"

Office::Office()
	:App() {}

Office::Office(const char *serialnum, const std::string& name,
		const std::string& os, Manufacturer *manf,
		int price, const std::vector<std::string>& ext)
	:App(serialnum, name, os, manf, price), extensions(ext) {}

Office::Office(const Office& o)
	:App(o.serialnum, o.name, o.os, o.manf, o.price) {}

Office::~Office()
{
	if (!extensions.empty()) extensions.clear();
}

void
Office::set_exts(const std::vector<std::string>& extensions)
{
	if (!this->extensions.empty()) this->extensions.clear();
	this->extensions = extensions;
}

void
Office::print(std::ostream& stream) const
{
	stream <<
		std::left << std::setw(7) << serialnum <<
		std::left << std::setw(20) << name <<
		std::left << std::setw(20) << os <<
		std::left << std::setw(7) << price;

	stream <<
		std::left << std::setw(7) << manf->get_serialnum() <<
		std::left << std::setw(15) << manf->get_name() <<
		std::left << std::setw(25) << manf->get_email();
	
	stream <<
		std::left << std::setw(10) << "N/A" <<
		std::left << std::setw(10) << "N/A";

	for (auto& ext : extensions)
		stream << ext << " ";
	
	std::vector<Review *> revs = get_revs();
	if (!reviews.empty())
	{
		stream << std::endl << std::endl << std::left << "Reviews:" << std::endl;
		stream << 
			std::left << std::setw(7) << "Stars" <<
			std::left << std::setw(25) << "Username" <<
			std::left << "Comment" << std::endl << std::endl;

		for (auto& rev : reviews)
			stream <<
				std::left << std::setw(7) << rev->get_stars() <<
				std::left << std::setw(25) << rev->get_username() <<
				std::left << rev->get_comment() << std::endl;
	}
	stream << std::endl;
}
