#pragma once
#include "Player.h"
#include "Ball.h"

class GameController final
{
public:
	explicit GameController(const sf::RenderWindow& window);

	void Update(sf::Time elapsed);
	void Draw(sf::RenderWindow& window) const;
	void CheckInput(sf::Event event);

private:
	Player _player;
	Ball _ball;
	std::vector<sf::RectangleShape> _walls;
	int _life;

	float _height;

	void launchBall();
};