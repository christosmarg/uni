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

		void addrev(Review *rev) {reviews.push_back(rev);}
		void addrevs(const std::vector<Review *> revs)
			{reviews.insert(reviews.end(), revs.begin(), revs.end());}

		inline const std::string& get_name() const {return name;}
		inline const std::string& get_os()   const {return os;}
		inline const Manufacturer get_manf() const {return Manufacturer(*manf);}
		inline constexpr const char *get_serialnum() const {return serialnum;}
		inline constexpr const std::vector<Review *>& get_revs() const {return reviews;}
		inline constexpr int get_price() const {return price;}

		void set_serialnum(const char *serialnum);
		inline void set_name(const std::string& name) {this->name = name;}
		inline void set_os(const std::string& os)	  {this->os = os;}
		inline void set_manf(Manufacturer *manf)      {this->manf = manf;}
		inline void set_price(int price)			  {this->price = price;}

		virtual void print(std::ostream& stream) const = 0;
	
	private:
		char *convsn(const char *serialnum);
};

#endif /* APP_H */
