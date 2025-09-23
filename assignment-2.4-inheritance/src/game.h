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

		const std::string& get_genre() const override;
		bool get_online() const override;
};

#endif /* GAME_H */
