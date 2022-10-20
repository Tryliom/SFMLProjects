#include "Game.h"

#include "Random.h"

Game::Game() : _window(sf::VideoMode(1000, 700), "Snake"), _opponent(true)
{
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(144);

	_font.loadFromFile("data/font/pixelmix.ttf");

	_clock = sf::Clock();

	_comboDuration = sf::milliseconds(0);
	_lost = false;
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

		sf::Vector2u size = _window.getSize();

        // Graphical Region
        _window.clear(sf::Color::Black);

        // Draw snake
		if (!_lost)
		{
			_window.draw(_player);
			_window.draw(_opponent);
			_window.draw(_egg);
		}
		else
		{
			sf::Text gameOver;
			gameOver.setString(sf::String("Game Over"));
			gameOver.setFont(_font);
			gameOver.setCharacterSize(50);
			gameOver.setPosition(size.x / 2, size.y / 2);
			gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height / 2);
			gameOver.setFillColor(sf::Color(255, 100, 100));

			_window.draw(gameOver);
		}

		sf::Text score;
		score.setString(sf::String("Score: " + std::to_string(_score) + " pts"));
		score.setFont(_font);
		score.setCharacterSize(20);
		score.setPosition(30, 10);
		score.setFillColor(sf::Color(255, 255, 255, 155));

		_window.draw(score);

		sf::Text combo;
		combo.setString(sf::String("Combo x" + std::to_string(_combo)));
		combo.setFont(_font);
		combo.setCharacterSize(20);
		combo.setPosition(30, 40);
		combo.setFillColor(sf::Color(255, 255, 255, 155));

		_window.draw(combo);

		if (_comboDuration > sf::Time::Zero)
		{
			sf::RectangleShape comboLine;
			float height = static_cast<float>(size.y) * 
				static_cast<float>(_comboDuration.asMicroseconds()) / 
				static_cast<float>(COMBO_MAX_DURATION.asMicroseconds());

			comboLine.setFillColor(sf::Color(255, 255, 255, 255));
			comboLine.setPosition(10, 10);
			comboLine.setSize(sf::Vector2f(10, height));

			_window.draw(comboLine);
		}

        // Window Display
        _window.display();
    }
}

void Game::update(const sf::Time elapsed)
{
	if (!_lost)
	{
		_player.Update(elapsed, _egg.GetPosition());
		_opponent.Update(elapsed, _egg.GetPosition());

		if (_player.Hit(_opponent.GetPositions()))
		{
			_player.TakeDamage();

			if (static_cast<int>(_player.GetPositions().size()) <= 1)
			{
				_lost = true;
				return;
			}
		}

		if (_opponent.Hit(_player.GetPositions()))
		{
			_opponent.TakeDamage();
			_score += 5;
			_comboDuration += sf::milliseconds(500);

			if (_comboDuration > COMBO_MAX_DURATION)
			{
				_comboDuration = COMBO_MAX_DURATION;
			}
		}

		if (_player.CanEatEgg(_egg.GetPosition()))
		{
			setEggPosition();
			_player.Grow();
			_score += 10;
			_score += _combo;
			_comboDuration = COMBO_MAX_DURATION;
			_combo++;
		}

		if (_opponent.CanEatEgg(_egg.GetPosition()))
		{
			setEggPosition();
			_opponent.Grow();
		}

		if (_comboDuration < sf::Time::Zero)
		{
			_comboDuration = sf::Time::Zero;
			_combo = 0;
		}
		else
		{
			_comboDuration -= elapsed;
		}
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
