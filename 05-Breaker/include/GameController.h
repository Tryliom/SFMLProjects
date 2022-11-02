#pragma once
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

#include "SFML/Audio.hpp"

enum class Audio;

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
	std::vector<Brick> _bricks;

	// Walls
	sf::RectangleShape _topWall;
	sf::RectangleShape _leftWall;
	sf::RectangleShape _rightWall;

	sf::RectangleShape _background;
	sf::Font _font;
	sf::Music _music;
	sf::Sound _sounds;

	int _life;
	int _score;
	int _ballsLeft;

	float _height;
	float _width;

	void launchBall();
	void createBricks();
	void createWalls(const sf::RenderWindow& window);
	void playSound(Audio audio);
};
