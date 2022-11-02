#pragma once
#include "Animation.h"
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
	void CheckInput(sf::Event event, sf::RenderWindow& window);

private:
	Player _player;
	std::vector<Ball> _balls;
	std::vector<Brick> _bricks;
	std::vector<Spark> _sparks;
	std::vector<Animation*> _animations;

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
	float _ultimateCharge;

	float _height;
	float _width;

	void launchBall();
	void playSound(Audio audio);

	void drawUltimateBar(sf::RenderWindow& window) const;
	void useUltimate();

	void createBricks();
	void createWalls(const sf::RenderWindow& window);
	void createSparks(const sf::Vector2f& position);

	bool hasLost() const { return _life <= 0; }
};
