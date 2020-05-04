#include "appsystem.h"
#include <iomanip>

std::ostream& operator<< (std::ostream& stream, const AppSystem& sys)
{
	stream <<
		std::left << std::setw(7) << "SN" <<
		std::left << std::setw(20) << "Name" <<
		std::left << std::setw(20) << "OS" <<
		std::left << std::setw(7) << "Price" <<
		std::left << std::setw(7) << "SN" <<
		std::left << std::setw(15) << "Manufacturer" <<
		std::left << std::setw(25) << "Email" <<
		std::left << std::setw(10) << "Genre" <<
		std::left << std::setw(10) << "Online" <<
		std::left << std::setw(25) << "Extensions" << std::endl << std::endl;

	std::vector<App *> apps = sys.get_apps();
	for (auto& app : apps)
	{

		stream <<
			std::left << std::setw(7) << app->get_serialnum() <<
			std::left << std::setw(20) << app->get_name() <<
			std::left << std::setw(20) << app->get_os() <<
			std::left << std::setw(7) << app->get_price();

		Manufacturer m = app->get_manf();
		stream <<
			std::left << std::setw(7) << m.get_serialnum() <<
			std::left << std::setw(15) << m.get_name() <<
			std::left << std::setw(25) << m.get_email();

		Game *o = dynamic_cast<Game *>(app);
		stream << std::left << std::setw(10) << (o ? o->get_genre() : "N/A");
		stream << std::left << std::setw(10) <<
			(o ? (o->get_online() ? "Yes" : "No") : "N/A");
		
		if (Office *of = dynamic_cast<Office *>(app))
		{
			std::vector<std::string> exts = of->get_exts();
			for (auto& ext : exts)
				stream << ext << " ";
		}
		else stream << "N/A";
		
		std::vector<Review *> revs = app->get_revs();
		if (!revs.empty())
		{
			stream << std::endl << std::endl << std::left << "Reviews:" << std::endl;
			stream << 
				std::left << std::setw(7) << "Stars" <<
				std::left << std::setw(25) << "Username" <<
				std::left << "Comment" << std::endl << std::endl;

			for (auto& rev : revs)
				stream <<
					std::left << std::setw(7) << rev->get_stars() <<
					std::left << std::setw(25) << rev->get_username() <<
					std::left << rev->get_comment() << std::endl;
		}
		stream << std::endl;
	}
	return stream;	
}

int main(int argc, char **argv)
{
	AppSystem sys;
	Manufacturer *comp = new Manufacturer("0004", "Company", "comp@comp.com");
	Manufacturer *chris = new Manufacturer("0005", "Chris", "chris@chris.com");
	sys += comp;
	sys += chris;
	if (!sys.import_data<Manufacturer>("res/manfdata.csv")) return -1;
	if (!sys.import_data<App>("res/appdata.csv")) return -1;
	if (!sys.import_data<Review>("res/revs.csv")) return -1;
	std::vector<std::string> ext = {".doc", ".xls", ".ppt"};
	sys += new Office("0004", "OpenOffice", "MAD Robot 2.2", comp, 0, ext);
	sys += new Game("0005", "minecurses", "MAD Robot 1.0", chris, 0, "Puzzle", false);

	sys.newrev("minecurses", new Review(4, "Name Surnaming", "Good"));
	std::cout << sys << std::endl;

	sys.removebad(chris);

	std::vector<Office *> fapps = sys.get_freeapps();
	std::vector<Game *> ggames = sys.get_goodgames();
	for (auto& fapp : fapps)
		std::cout << fapp->get_name() << std::endl;
	for (auto& ggame : ggames)
		std::cout << ggame->get_name() << std::endl;

	if (!sys.export_data<Manufacturer>("res/manfdata_out.csv")) return -1;
	if (!sys.export_data<App>("res/appdata_out.csv")) return -1;
	if (!sys.export_data<Review>("res/revs_out.csv")) return -1;

	return 0;
}
