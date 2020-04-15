#ifndef APPSTREAM_H
#define APPSTREAM_H

#include <string>
#include <vector>

class AppSystem
{
	private:
		std::vector<std::string> applist;
		std::vector<const char *> manufacturers;

	public:
		AppSystem();
		virtual ~AppSystem();

		inline void operator+= (const std::string& app) {this->applist.push_back(app);}
		inline void operator+= (const char *man) {this->manufacturers.push_back(man);}
};

#endif /* APPSYSTEM_H */
