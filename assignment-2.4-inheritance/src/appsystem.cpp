#include "appsystem.h"

AppSystem::AppSystem() {}

AppSystem::~AppSystem() {}

void AppSystem::operator+= (const std::string& app)
{
	apps.push_back(app);
}

void AppSystem::operator+= (const char *man)
{
	manufacturers.push_back(man);
}
