#include <memory>
#include "appsystem.hpp"

static std::ostream& operator<< (std::ostream& stream, const AppSystem& sys);
static void cont(const char *s);
static void pluseqs(AppSystem& sys);
static void edit(AppSystem& sys);
static void remove(AppSystem& sys);
static void getapps(const AppSystem& sys);

/* 
 * main uses smart pointers just so I don't have to delete
 * them manually. There's obviously no good reason to do it
 * as there's only one object, but it looks cool.
 *
 * I also used some features that might make the program harder
 * to understand, but I wanted to take a chance and try out some of
 * these features, for fun mainly, even though they might seem
 * (and be) useless.
 */
int
main(int argc, char **argv)
{
    std::unique_ptr<AppSystem> sys = std::make_unique<AppSystem>();
    system("clear || cls");
    sys->import_data<Manufacturer>("res/manfdata.csv");
    sys->import_data<App>("res/appdata.csv");
    sys->import_data<Review>("res/revs.csv");

    cont("Imported data");
    std::cout << *sys << std::endl;
    
    pluseqs(*sys);
    cont("Additional data");
    std::cout << *sys << std::endl;

    edit(*sys);
    cont("Editing data");
    std::cout << *sys << std::endl;

    remove(*sys);
    cont("Removing data");
    std::cout << *sys << std::endl;

    cont("");
    getapps(*sys);

    cont("");
    sys->export_data<Manufacturer>("res/manfdata_out.csv");
    sys->export_data<App>("res/appdata_out.csv");
    sys->export_data<Review>("res/revs_out.csv");
    std::printf("\nThank you :)\n");

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

void
cont(const char *s)
{
    std::printf("\nPress <ENTER> to continue. . .");
    if (std::cin.get()) system("clear || cls");
    if (strlen(s) > 0) std::printf("%s\n\n", s);
}

void
pluseqs(AppSystem& sys)
{
    Manufacturer *comp = new Manufacturer("0004", "Company", "comp@comp.com");
    Manufacturer *chris = new Manufacturer("0005", "Chris", "chris@chris.com");
    sys += comp;
    sys += chris;
    sys += new Office("0004", "zathura", "NiceOS 1.1", comp, 0, {".pdf", ".md"});
    sys += new Game("0005", "minecurses", "NiceOS 0.5", chris, 0, "Puzzle", false);
}

void
edit(AppSystem& sys)
{
    sys.call<Review *>("minecurses", new Review(5, "gamer", "Good game"),
            &App::addrev);
    sys.call<const std::vector<Review *>>("Vim",
            {new Review(2, "user1", "Not so good"),
             new Review(4, "user2", "Good app"),
             new Review(5, "user3", "Very good :)")},
             &App::addrevs);
    sys.call<const char *>("zathura", "1254", &App::set_serialnum);
    sys.call<const std::string&>("minecurses", "minesweeper", &App::set_name);
    sys.call<const std::string&>("Vim", "GoodOS", &App::set_os);
    sys.call<Manufacturer *>("LibreOffice",
            new Manufacturer("0006", "FreeSoftware", "freesoft@freesoft.com"),
            &App::set_manf);
    sys.call<int>("LoL", 155, &App::set_price);
    sys.cast_call<const std::string&, Game>("CS:GO", "Shooter", &Game::set_genre);
    sys.cast_call<bool, Game>("minesweeper", true, &Game::set_online);
    sys.cast_call<const std::vector<std::string>&, Office>("zathura",
            {".tex", ".epub", ".ms"}, &Office::set_exts);
}

void
remove(AppSystem& sys)
{
    sys.removebad("0003");
}

void
getapps(const AppSystem& sys)
{
    const std::vector<Office *>& fapps = sys.get_freeapps();
    const std::vector<Game *>& ggames = sys.get_goodgames();
    std::cout << "Free office apps: " << std::endl << std::endl;
    for (const auto& fapp : fapps)
        std::cout << fapp->get_name() << std::endl;
    std::cout << std::endl;
    std::cout << "Games with >4 rating: " << std::endl << std::endl;
    for (const auto& ggame : ggames)
        std::cout << ggame->get_name() << std::endl;
}
