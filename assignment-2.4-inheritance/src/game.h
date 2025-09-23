#ifndef GAME_H
#define GAME_H

#include "app.h"

class Game: public App
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

        inline const std::string get_genre() const {return genre;}
        inline constexpr bool get_online()   const {return online;}
        inline void set_genre(const std::string& genre) {this->genre = genre;}
        inline void set_online(bool online) {this->online = online;}
        virtual void print(std::ostream& stream) const override;
};

#endif /* GAME_H */
