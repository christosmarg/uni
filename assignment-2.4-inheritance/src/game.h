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

		const std::string get_genre() const;
		bool get_online() const;

		void set_genre(const std::string& genre);
		void set_online(bool online);
		virtual void print(std::ostream& stream) const override;
};

#endif /* GAME_H */
