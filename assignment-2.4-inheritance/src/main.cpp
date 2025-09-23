#include "appsystem.h"

std::ostream& operator<< (std::ostream& stream, const AppSystem& sys)
{
	std::vector<App *> apps = sys.get_apps();
	for (auto& app : apps)
	{
		Manufacturer m = app->get_manf();
		stream <<
			app->get_serialnum() << " " <<
			app->get_name() << " " <<
			app->get_os() << " " <<
			app->get_price() << " ";

		if (Office *o = dynamic_cast<Office *>(app))
		{
			std::vector<std::string> exts = o->get_exts();
			for (auto& ext : exts)
				stream << ext << " ";		
		}
		else if (Game *o = dynamic_cast<Game *>(app))
		{
			stream <<
				o->get_genre() << " " <<
				o->get_online() << " ";
		}
		
		std::vector<Review *> revs = app->get_revs();
		if (!revs.empty())
			for (auto& rev : revs)
				stream <<
					rev->get_stars() << " " <<
					rev->get_username() << " " <<
					rev->get_comment() <<  " ";

		stream <<
			m.get_serialnum() << " " <<
			m.get_name() << " " <<
			m.get_email();

		stream << std::endl;
	}
	return stream;	
}

int main(int argc, char **argv)
{
	AppSystem sys;
	Manufacturer *gnu = new Manufacturer("1234", "GNU", "gnu@gnu.com");
	Manufacturer *cm = new Manufacturer("5678", "Chris", "chris@cm.com");
	sys += gnu;
	sys += cm;
	if (!sys.read_data("res/data.csv")) return -1;
	std::vector<std::string> ext = {".doc", ".xls", ".ppt"};
	sys += new Office("132456", "LibreOffice", "Linux 2.2", gnu, 0, ext);
	sys += new Game("731234", "minecurses", "Linux 4.5", cm, 0, "Puzzle", false);

	Review rev(6, "Name Surnaming", "Good");
	sys.newrev("minecurses", &rev);
	std::cout << sys << std::endl;

	sys.removebad(cm);
	std::cout << sys << std::endl;

	std::vector<Office *> fapps = sys.get_freeapps();
	std::vector<Game *> ggames = sys.get_goodgames();
	for (auto& fapp : fapps)
		std::cout << fapp->get_name() << std::endl;
	for (auto& ggame : ggames)
		std::cout << ggame->get_name() << std::endl;

	if (!sys.export_data("res/output.csv")) return -1;

	return 0;
}
