#pragma once
#include "Egg.h"
#include "Snake.h"

class Game
{
public:
	Game();

	void Start();
private:
	sf::RenderWindow _window;
	Snake _player;
	Snake _opponent;
	Egg _egg;
	sf::Clock _clock;

	void update(sf::Time elapsed);
	void setEggPosition();
};
