#ifndef GAME_HPP
#define GAME_HPP

#include "app.hpp"

class Game final: public App
{
    private:
        std::string genre;
        bool online;

    public:
        Game();
        Game(const char *serialnum, const std::string& name,
             const std::string& os, Manufacturer *manf, int price,
             const std::string& genre, bool online);
        Game(const Game& g);

        const std::string get_genre() const {return genre;}
        constexpr const bool get_online() const {return online;}
        void set_genre(const std::string& genre) {this->genre = genre;}
        void set_online(const bool online) {this->online = online;}
        void print(std::ostream& stream) const override;
};

#endif /* GAME_HPP */
