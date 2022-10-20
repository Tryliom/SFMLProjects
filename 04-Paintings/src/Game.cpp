#include "Game.h"

#include <SFML/Graphics.hpp>

Game::Game() : _window(sf::VideoMode(1000, 700), "Paintings")
{
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(144);

	_drawable = PaintingFactory::GetPainting(_paintingType, _window.getSize());
}

void Game::Start()
{
	while (_window.isOpen())
    {
    	sf::Event event{};

        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window.close();
            }

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					_drawable = PaintingFactory::GetPainting(_paintingType, _window.getSize());
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					_paintingType = static_cast<PaintingType>(static_cast<int>(_paintingType) + 1);

					if (_paintingType == PaintingType::END)
					{
						_paintingType = static_cast<PaintingType>(0);
					}

					_drawable = PaintingFactory::GetPainting(_paintingType, _window.getSize());
				}
			}
		}

		_window.clear(sf::Color::White);
		
		if (_drawable != nullptr)
		{
			_window.draw(*_drawable);
		}

		_window.display();
	}
}