#ifndef APP_H
#define APP_H

#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "manufacturer.h"
#include "review.h"

class App
{
	protected:
		const char *serialnum;
		std::string name;
		std::string os;
		Manufacturer *manf;
		std::vector<Review *> reviews;
		int price;

	public:
		App();
		App(const char *serialnum, const std::string& name,
				const std::string& os, Manufacturer *manf, int price);
		App(const App& app);
		virtual ~App(); 

		void addrev(Review *rev);
		void addrevs(const std::vector<Review *> revs);

		const char *get_serialnum() const;
		const std::string& get_name() const;
		const std::string& get_os() const;
		const Manufacturer get_manf() const;
		const std::vector<Review *>& get_revs() const;
		int get_price() const;

		void set_serialnum(const char *serialnum);
		void set_name(const std::string& name);
		void set_os(const std::string& os);
		void set_manf(Manufacturer *manf);
		void set_price(int price);

		virtual void print(std::ostream& stream) const = 0;
	
	private:
		char *convsn(const char *serialnum);
};

#endif /* APP_H */
