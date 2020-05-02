#include "game.h"

Game::Game()
	:App(), genre(""), online(false) {}

Game::Game(const char *serialnum, const std::string& name,
		const std::string& os, Manufacturer *manf, int price,
		const std::string& genre, bool online)
	:App(serialnum, name, os, manf, price), genre(genre), online(online)
{
	try
	{
		if (genre.empty() || genre == "") throw genre;
	}
	catch (const std::string& genre)
	{
		throw std::runtime_error("Empty game genre.");
	}
}

const std::string Game::get_genre() const
{
	return genre;
}

bool Game::get_online() const
{
	return online;
}

void Game::set_genre(const std::string& genre)
{
	this->genre = genre;
}

void Game::set_online(bool online)
{
	this->online = online;
}
