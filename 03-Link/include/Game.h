#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

constexpr int SPEED = 1000;

class Game
{
public:
	Game();

private:
	sf::RenderWindow _window;
	sf::Clock _clock;
	std::unordered_map<Direction, sf::Texture> _directions;

	sf::Sprite _sprite;
	bool _isMoving{ false };

	void loadTextures();
public:
	void Start();
};
