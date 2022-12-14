#pragma once
#include "Egg.h"
#include "Snake.h"

const sf::Time COMBO_MAX_DURATION = sf::milliseconds(5000);
const sf::Time SPAWN_DURATION = sf::seconds(30);

class Game
{
public:
	Game();

	void Start();
private:
	sf::RenderWindow _window;
	sf::Clock _clock;
	sf::Font _font;

	Snake _player;
	Snake _opponent;
	Egg _egg;

	int _score{ 0 };
	int _combo{ 0 };
	// The combo duration time when you can increase your combo
	sf::Time _comboDuration;
	sf::Time _opponentSpawnTime;

	void update(sf::Time elapsed);
	void setEggPosition();
};
