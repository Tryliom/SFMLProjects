#include "Game.h"

#include "Random.h"

Game::Game() : _window(sf::VideoMode(1000, 700), "Snake"), _opponent(true)
{
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(144);

	_clock = sf::Clock();
}

void Game::Start()
{
    while (_window.isOpen())
    {
	    const sf::Time elapsed = _clock.restart();
        update(elapsed);

        sf::Event event{};

        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
				if (event.key.code == sf::Keyboard::Left && _player.GetDirection() != Direction::RIGHT)
				{
					_player.ChangeDirection(Direction::LEFT);
				}
				else if (event.key.code == sf::Keyboard::Right && _player.GetDirection() != Direction::LEFT)
				{
					_player.ChangeDirection(Direction::RIGHT);
				}
				else if (event.key.code == sf::Keyboard::Up && _player.GetDirection() != Direction::DOWN)
				{
					_player.ChangeDirection(Direction::UP);
				}
                else if (event.key.code == sf::Keyboard::Down && _player.GetDirection() != Direction::UP)
                {
                    _player.ChangeDirection(Direction::DOWN);
                }
            }
        }

        // Graphical Region
        _window.clear(sf::Color::Black);

        // Draw snake
        _window.draw(_player);
		_window.draw(_opponent);
    	_window.draw(_egg);

        // Window Display
        _window.display();
    }
}

void Game::update(const sf::Time elapsed)
{
	_player.Update(elapsed, _egg.GetPosition());
	_opponent.Update(elapsed, _egg.GetPosition());

	_player.CheckCollisions(_opponent.GetPositions());
	_opponent.CheckCollisions(_player.GetPositions());

	if (_player.CanEatEgg(_egg.GetPosition()))
	{
		setEggPosition();
		_player.Grow();
	}

	if (_opponent.CanEatEgg(_egg.GetPosition()))
	{
		setEggPosition();
		_opponent.Grow();
	}
}

void Game::setEggPosition()
{
	constexpr int offset = 30;
	std::vector<sf::Vector2f> denyPositions = _player.GetPositions();
	std::vector<sf::Vector2f> validPositions = {};

	denyPositions.emplace_back(_egg.GetPosition());

	for (int width = offset; width < _window.getSize().x; width += SPEED * 2)
	{
		for (int height = offset; height < _window.getSize().y; height += SPEED * 2)
		{
			const sf::Vector2f position{ static_cast<float>(width), static_cast<float>(height) };

			if (std::find(denyPositions.begin(), denyPositions.end(), position) == denyPositions.end())
			{
				validPositions.emplace_back(position);
			}
		}
	}

	_egg.SetPosition(validPositions[Random::GetInt(0, static_cast<int>(validPositions.size()) - 1)]);
}
