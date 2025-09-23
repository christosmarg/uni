#ifndef GAME_H
#define GAME_H

#include "manufacturer.h"
#include "review.h"

class Game : public Manufacturer, public Review
{
	private:
		std::string genre;
		std::string os;
		bool online;
		int price;

	public:
		Game();
		~Game();
};

#endif /* GAME_H */
