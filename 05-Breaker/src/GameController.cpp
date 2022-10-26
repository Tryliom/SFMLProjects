#include "GameController.h"

#include <iostream>

GameController::GameController(const sf::RenderWindow& window)
	: _player( sf::Vector2f( window.getSize().x / 2, window.getSize().y - 50 ) )
{
	// Create wall around the screen
	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(window.getSize().x, 10)));
	_walls.back().setPosition(0, 0);
	_walls.back().setFillColor(sf::Color::White);

	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(10, window.getSize().y)));
	_walls.back().setPosition(0, 0);
	_walls.back().setFillColor(sf::Color::White);

	_walls.emplace_back(sf::RectangleShape(sf::Vector2f(10, window.getSize().y)));
	_walls.back().setPosition(window.getSize().x - 10, 0);
	_walls.back().setFillColor(sf::Color::White);

	_height = static_cast<float>(window.getSize().y);

	_life = 3;
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

	if (_ball.IsMoving())
	{
		_ball.Update(elapsed);

		for (Bar& bar : _player.GetBars())
		{
			if (_ball.IsColliding(bar.GetBar()))
			{
				_ball.Bounce(bar);
			}
		}

		for (const auto& wall : _walls)
		{
			if (_ball.IsColliding(wall))
			{
				_ball.Bounce(wall);
				//break;
			}
		}
	}
	else
	{
		_ball.SetPosition(_player.GetBallPosition() + sf::Vector2f(0, -_ball.GetRadius()));
	}

	if (_ball.GetPosition().y > _height)
	{
		_ball.Reset();
		_life--;
	}
}

void GameController::Draw(sf::RenderWindow& window) const
{
	window.draw(_player);
	window.draw(_ball);

	for (const auto& wall : _walls)
	{
		window.draw(wall);
	}
}

void GameController::CheckInput(const sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space && !_ball.IsMoving())
		{
			launchBall();
		}
	}
}

void GameController::launchBall()
{
	_ball.Launch(sf::Vector2f(100.0f, -150.0f));
}
