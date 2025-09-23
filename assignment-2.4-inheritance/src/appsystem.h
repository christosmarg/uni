#ifndef APPSTREAM_H
#define APPSTREAM_H

#include <string>
#include <vector>

class AppSystem
{
	private:
		std::vector<std::string> apps;
		std::vector<const char *> manufacturers;

	public:
		AppSystem();
		virtual ~AppSystem();

		void operator+= (const std::string& app);
		void operator+= (const char *man);
};

#endif /* APPSYSTEM_H */
