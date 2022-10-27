#pragma once
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

#include "SFML/Audio.hpp"

class GameController final
{
public:
	explicit GameController(sf::RenderWindow& window);

	void Update(sf::Time elapsed);
	void Draw(sf::RenderWindow& window) const;
	void CheckInput(sf::Event event);

private:
	Player _player;
	std::vector<Ball> _balls;
	std::vector<sf::RectangleShape> _walls;
	std::vector<Brick> _bricks;

	sf::RectangleShape _background;
	sf::Texture _backgroundTexture;
	sf::Font _font;
	sf::Music _music;
	sf::Sound _hitSound;

	int _life;
	int _score;
	int _ballsLeft;

	float _height;
	float _width;

	void launchBall();
	void createBricks();
	void createWalls(sf::RenderWindow& window);
};
