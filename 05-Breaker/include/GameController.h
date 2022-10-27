#pragma once
#include "Player.h"
#include "Ball.h"

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

	sf::RectangleShape _background;
	sf::Texture _backgroundTexture;
	sf::Font _font;

	int _life;
	int _score;
	int _ballsLeft;

	float _height;
	float _width;

	void launchBall();
};