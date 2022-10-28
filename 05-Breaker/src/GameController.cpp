#include "GameController.h"

#include <iostream>

#include "Random.h"

GameController::GameController(sf::RenderWindow& window)
	: _player( sf::Vector2f( window.getSize().x / 2, window.getSize().y - 50 ) )
{
	_width = static_cast<float>(window.getSize().x);
	_height = static_cast<float>(window.getSize().y);
	_life = 3;
	_score = 0;
	_ballsLeft = 3;
	_balls.emplace_back();

	_backgroundTexture.loadFromFile("data/textures/background.png");
	_background.setSize(sf::Vector2f(_width, _height));
	_background.setTexture(&_backgroundTexture);

	_font.loadFromFile("data/font/pixelmix.ttf");

	createBricks();
	createWalls(window);

	/*_music.openFromFile("data/sound/main_theme.wav");
	_music.play();*/
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

	if (_life != 0)
	{
		_player.Update(elapsed);
	}

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
					onBounce(bar);
				}
			}

			for (const auto& wall : _walls)
			{
				if (ball.IsColliding(wall))
				{
					ball.Bounce(wall);
					//onBounce(wall);
				}
			}

			for (auto& brick : _bricks)
			{
				if (ball.IsColliding(brick.GetShape()))
				{
					ball.Bounce(brick.GetShape());
					onBounce(brick);
					brick.Break();
					_score += 10;
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
			return ball.GetPosition().y > _height * 1.5f;
	}), _balls.end());

	if (_balls.empty() && _life != 0)
	{
		_life--;

		if (_life != 0)
		{
			_ballsLeft = 3;
			_balls.emplace_back();
		}
	}

	// Delete bricks that are broken
	_bricks.erase(std::remove_if(_bricks.begin(), _bricks.end(), [](const Brick& brick)
		{
			return brick.IsDestroyed();
		}
	), _bricks.end());
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

	for (const auto& brick : _bricks)
	{
		window.draw(brick);
	}

	sf::Text scoreText;
	scoreText.setFont(_font);
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 4);
	scoreText.setString(std::to_string(_score) + " pts");

	window.draw(scoreText);

	sf::Text lifeText;
	lifeText.setFont(_font);
	lifeText.setCharacterSize(16);
	lifeText.setFillColor(sf::Color::White);
	lifeText.setString("Life: " + std::to_string(_life));
	lifeText.setPosition(_width - lifeText.getGlobalBounds().width - 10, 4);

	window.draw(lifeText);

	if (_life == 0)
	{
		sf::Text gameOverText;
		gameOverText.setFont(_font);
		gameOverText.setCharacterSize(30);
		gameOverText.setFillColor(sf::Color::Black);
		gameOverText.setOutlineColor(sf::Color::White);
		gameOverText.setOutlineThickness(2);
		gameOverText.setString("GAME OVER");
		gameOverText.setPosition(_width / 2 - gameOverText.getGlobalBounds().width / 2, _height / 2 - gameOverText.getGlobalBounds().height / 2);

		window.draw(gameOverText);
	}
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

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			launchBall();
		}
	}

	if (event.type == sf::Event::MouseMoved)
	{
		// Update player with the mouse position
		const float size = _player.GetBars()[0].GetBar().getSize().x / 2;
		int x = event.mouseMove.x;

		if (x < 0)
		{
			x = 0;
		}
		else if (x + size > _width)
		{
			x = _width - size;
		}
		
		_player.SetPosition(x - size);
	}
}

void GameController::launchBall()
{
	for (auto& ball : _balls)
	{
		if (!ball.IsMoving())
		{
			float velocity = _player.GetVelocity();

			if (velocity == 0.0f)
			{
				velocity = Random::GetFloat(120.0f, 200.0f);
			}

			ball.Launch(sf::Vector2f(velocity, -200.0f));
			_ballsLeft--;

			if (_ballsLeft > 0)
			{
				_balls.emplace_back();
			}

			break;
		}
	}
}

void GameController::createBricks()
{
	const int nbBrickOnWidth = static_cast<int>((_width - 2 * 30) / BRICK_WIDTH);
	const int nbBrickOnHeight = static_cast<int>(_height / 3 / BRICK_HEIGHT);
	const float brickMargin = ((_width - 2 * 30) - nbBrickOnWidth * BRICK_WIDTH) / (nbBrickOnWidth - 1);

	// Create bricks
	for (int w = 0; w < nbBrickOnWidth; w++)
	{
		for (int h = 0; h < nbBrickOnHeight; h++)
		{
			_bricks.emplace_back(Brick(sf::Vector2f(
				30.0f + (BRICK_WIDTH + brickMargin) * w,
				80.0f + (BRICK_HEIGHT + brickMargin) * h
			)));
		}
	}
}

void GameController::createWalls(sf::RenderWindow& window)
{
	const sf::Color wallColor = sf::Color(0, 0, 0, 200);

	// Create wall around the screen
	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(window.getSize().x + 100, 24 + 50)));
	_walls.back().setPosition(-50, -50);
	_walls.back().setFillColor(wallColor);

	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(20, window.getSize().y)));
	_walls.back().setPosition(-20, 24);
	_walls.back().setFillColor(sf::Color::Transparent);

	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(20, window.getSize().y)));
	_walls.back().setPosition(window.getSize().x, 24);
	_walls.back().setFillColor(sf::Color::Transparent);
}

void GameController::onBounce(sf::Drawable& object)
{
	//TODO: Play sounds and display effect when ball bounce on an object, depending on the object
}
