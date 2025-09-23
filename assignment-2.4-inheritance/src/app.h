#ifndef APP_H
#define APP_H

#include <string>
#include <string.h>
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
		virtual ~App(); 

		char *convsn(const char *serialnum);
		void addrev(Review *rev);

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

		virtual const std::string get_genre() const {return {};} 
		virtual bool get_online() const {return false;} // not good
		virtual void set_genre(const std::string& genre) {}
		virtual void set_online(bool online) {}
		virtual const std::vector<std::string> get_exts() const {return {};}
		virtual void set_exts(const std::vector<std::string>& extensions) {}
};

#endif /* APP_H */
