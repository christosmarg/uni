#include "game.hpp"

Game::Game()
    :App(), genre(""), online(false) {}

Game::Game(const char *serialnum, const std::string& name,
        const std::string& os, Manufacturer *manf, const int price,
        const std::string& genre, const bool online)
    :App(serialnum, name, os, manf, price), genre(genre), online(online)
{
    if (genre.empty() || genre == "")
        errlog.write("Game: " + std::string(serialnum) + ": Empty genre");
}

Game::Game(const Game& g)
    :App(g.serialnum, g.name, g.os, g.manf, g.price), genre(g.genre),
    online(g.online) {}

void
Game::print(std::ostream& stream) const
{
    stream <<
        std::left << std::setw(7) << serialnum <<
        std::left << std::setw(20) << name <<
        std::left << std::setw(20) << os <<
        std::left << std::setw(7) << price;

    stream <<
        std::left << std::setw(7) << manf->get_serialnum() <<
        std::left << std::setw(15) << manf->get_name() <<
        std::left << std::setw(25) << manf->get_email();

    stream <<
        std::left << std::setw(10) << genre <<
        std::left << std::setw(10) << (online ? "Yes" : "No");
    stream << "N/A";

    if (!reviews.empty())
    {
        stream << std::endl << std::endl << std::left << "Reviews:" << std::endl;
        stream << 
            std::left << std::setw(7) << "Stars" <<
            std::left << std::setw(25) << "Username" <<
            std::left << "Comment" << std::endl << std::endl;

        for (auto& rev : reviews)
            stream <<
                std::left << std::setw(7) << rev->get_stars() <<
                std::left << std::setw(25) << rev->get_username() <<
                std::left << rev->get_comment() << std::endl;
    }
    stream << std::endl;
}
