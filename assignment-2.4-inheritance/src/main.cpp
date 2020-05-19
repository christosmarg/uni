#include "appsystem.h"

std::ostream& operator<< (std::ostream& stream, const AppSystem& sys);
static void cont(const char *s);
static void pluseqs(AppSystem& sys);
static void edit(AppSystem& sys);
static void remove(AppSystem& sys);
static void getapps(const AppSystem& sys);

int
main(int argc, char **argv)
{
	AppSystem sys;
	system("clear || cls");
	if (!sys.import_data<Manufacturer>("res/manfdata.csv")) return -1;
	if (!sys.import_data<App>("res/appdata.csv")) return -1;
	if (!sys.import_data<Review>("res/revs.csv")) return -1;

	cont("Imported data");
	std::cout << sys << std::endl;
	
	pluseqs(sys);
	cont("Additional data");
	std::cout << sys << std::endl;

	edit(sys);
	cont("Editing data");
	std::cout << sys << std::endl;

	remove(sys);
	cont("Removing data");
	std::cout << sys << std::endl;

	cont("");
	getapps(sys);

	cont("");
	if (!sys.export_data<Manufacturer>("res/manfdata_out.csv")) return -1;
	if (!sys.export_data<App>("res/appdata_out.csv")) return -1;
	if (!sys.export_data<Review>("res/revs_out.csv")) return -1;
	std::cout << std::endl << "Thank you :)" << std::endl;

	return 0;
}

std::ostream&
operator<< (std::ostream& stream, const AppSystem& sys)
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
	for (const auto& app : apps)
		app->print(stream);
	return stream;	
}

static void
cont(const char *s)
{
	std::cout << std::endl;
	std::cout << "Press <ENTER> to continue. . .";
	if (std::cin.get()) system("clear || cls");
	if (strlen(s) > 0) std::cout << s << std::endl << std::endl;
}

static void
pluseqs(AppSystem& sys)
{
	Manufacturer *comp = new Manufacturer("0004", "Company", "comp@comp.com");
	Manufacturer *chris = new Manufacturer("0005", "Chris", "chris@chris.com");
	sys += comp;
	sys += chris;
	std::vector<std::string> ext = {".pdf", ".md"};
	sys += new Office("0004", "zathura", "NiceOS 1.1", comp, 0, ext);
	sys += new Game("0005", "minecurses", "NiceOS 0.5", chris, 0, "Puzzle", false);
}

static void
edit(AppSystem& sys)
{
	sys.newrev("minecurses", new Review(5, "gamer", "Good game"));
	sys.newrevs("LibreOffice",
			{new Review(2, "user1", "Not so good"),
			 new Review(4, "user2", "Good app")});
	sys.chserialnum("zathura", "1254");
	sys.chname("minecurses", "minesweeper");
	sys.chos("Vim", "GoodOS");
	sys.chmanf("LibreOffice",
			new Manufacturer("0006", "FreeSoftware", "freesoft@freesoft.com"));
	sys.chprice("LoL", 155);
	sys.chgenre("CS:GO", "Shooter");
	sys.chonline("minesweeper", true);
	sys.chexts("zathura", {".exe", ".bin", ".dat"});
}

static void
remove(AppSystem& sys)
{
	sys.removebad("GNU");
}

static void
getapps(const AppSystem& sys)
{
	const std::vector<Office *>& fapps = sys.get_freeapps();
	const std::vector<Game *>& ggames = sys.get_goodgames();
	std::cout << "Free office apps: " << std::endl << std::endl;
	for (const auto& fapp : fapps)
		std::cout << fapp->get_name() << std::endl;
	std::cout << std::endl;
	std::cout << "Games with >5 rating: " << std::endl << std::endl;
	for (const auto& ggame : ggames)
		std::cout << ggame->get_name() << std::endl;
}
