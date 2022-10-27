#include "GameController.h"

GameController::GameController(sf::RenderWindow& window)
	: _player( sf::Vector2f( window.getSize().x / 2, window.getSize().y - 50 ) )
{
	// Create wall around the screen
	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(window.getSize().x, 14)));
	_walls.back().setPosition(0, 0);
	_walls.back().setFillColor(sf::Color::White);

	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(10, window.getSize().y)));
	_walls.back().setPosition(0, 0);
	_walls.back().setFillColor(sf::Color::White);

	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(10, window.getSize().y)));
	_walls.back().setPosition(window.getSize().x - 10, 0);
	_walls.back().setFillColor(sf::Color::White);

	_width = static_cast<float>(window.getSize().x);
	_height = static_cast<float>(window.getSize().y);
	_life = 3;
	_score = 0;
	_ballsLeft = 3;
	_balls.emplace_back(Ball());

	_backgroundTexture.loadFromFile("data/textures/background.png");
	_background.setSize(sf::Vector2f(_width, _height));
	_background.setTexture(&_backgroundTexture);

	_font.loadFromFile("data/font/pixelmix.ttf");
}

void GameController::Update(const sf::Time elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_player.MoveLeft(elapsed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_player.MoveRight(elapsed);
	}
	else
	{
		_player.ResetDirection();
	}

	_player.Update(elapsed);

	for (auto& wall : _walls)
	{
		if (_player.IsColliding(wall))
		{
			_player.Stop(wall);
		}
	}

	for (auto& ball : _balls)
	{
		ball.Update(elapsed);

		if (ball.IsMoving())
		{
			for (Bar& bar : _player.GetBars())
			{
				if (ball.IsColliding(bar.GetBar()))
				{
					ball.Bounce(bar);
				}
			}

			for (const auto& wall : _walls)
			{
				if (ball.IsColliding(wall))
				{
					ball.Bounce(wall);
				}
			}
		}
		else
		{
			ball.SetPosition(_player.GetBallPosition() + sf::Vector2f(0, -ball.GetRadius()));
		}
	}

	// Delete balls that are out of the screen
	_balls.erase(std::remove_if(_balls.begin(), _balls.end(), [this](const Ball& ball)
	{
		return ball.GetPosition().y > _height;
	}), _balls.end());

	if (_balls.empty())
	{
		_life--;
		_ballsLeft = 3;
		_balls.emplace_back(Ball());
	}
}

void GameController::Draw(sf::RenderWindow& window) const
{
	window.draw(_background);
	window.draw(_player);

	for (const auto& ball : _balls)
	{
		window.draw(ball);
	}

	for (const auto& wall : _walls)
	{
		window.draw(wall);
	}

	sf::Text scoreText;
	scoreText.setFont(_font);
	scoreText.setCharacterSize(12);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(10, 1);
	scoreText.setString(std::to_string(_score) + " pts");

	window.draw(scoreText);

	sf::Text lifeText;
	lifeText.setFont(_font);
	lifeText.setCharacterSize(12);
	lifeText.setFillColor(sf::Color::Black);
	lifeText.setString("Life: " + std::to_string(_life));
	lifeText.setPosition(_width - lifeText.getGlobalBounds().width - 10, 1);

	window.draw(lifeText);
}

void GameController::CheckInput(const sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			launchBall();
		}
	}
}

void GameController::launchBall()
{
	for (auto& ball : _balls)
	{
		if (!ball.IsMoving())
		{
			ball.Launch(sf::Vector2f(_player.GetVelocity(), -200.0f));
			_ballsLeft--;

			if (_ballsLeft > 0)
			{
				_balls.emplace_back(Ball());
			}

			break;
		}
	}
}
