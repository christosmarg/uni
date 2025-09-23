#include "game.h"

Game::Game()
	:App(), genre(""), online(false) {}

Game::Game(const char *serialnum, const std::string& name,
		const std::string& os, Manufacturer *manf, int price,
		const std::string& genre, bool online)
	:App(serialnum, name, os, manf, price), genre(genre), online(online) {}

const std::string& Game::get_genre() const
{
	return genre;
}

bool Game::get_online() const
{
	return online;
}
