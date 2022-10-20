#include "Game.h"

#include <SFML/Graphics.hpp>

Game::Game() : _window(sf::VideoMode(1000, 700), "It's LINK")
{
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(144);

	_clock.restart();

	loadTextures();

	sf::Vector2u size = _window.getSize();
	_sprite.setPosition(size.x / 2, size.y / 2);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_sprite.setTexture(_directions[Direction::DOWN]);

}

void Game::loadTextures()
{
	sf::Texture up;
	up.loadFromFile("data/textures/up.png");
	_directions.emplace(Direction::UP, up);

	sf::Texture down;
	down.loadFromFile("data/textures/down.png");
	_directions.emplace(Direction::DOWN, down);

	sf::Texture left;
	left.loadFromFile("data/textures/left.png");
	_directions.emplace(Direction::LEFT, left);

	sf::Texture right;
	right.loadFromFile("data/textures/right.png");
	_directions.emplace(Direction::RIGHT, right);
}

void Game::Start()
{
	const sf::Time elapsed = _clock.restart();

    while (_window.isOpen())
    {
    	sf::Event event{};

        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window.close();
            }
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			_sprite.setTexture(_directions.at(Direction::LEFT));
			_sprite.move(-SPEED * elapsed.asSeconds(), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			_sprite.setTexture(_directions.at(Direction::RIGHT));
			_sprite.move(SPEED * elapsed.asSeconds(), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			_sprite.setTexture(_directions.at(Direction::UP));
			_sprite.move(0, -SPEED * elapsed.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			_sprite.setTexture(_directions.at(Direction::DOWN));
			_sprite.move(0, SPEED * elapsed.asSeconds());
		}

		_window.clear();
		
		_window.draw(_sprite);

		_window.display();
	}
}