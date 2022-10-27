#include "Bar.h"

#include <iostream>

Bar::Bar(const sf::Vector2f position)
{
	if (!_texture.loadFromFile("data/textures/bar.png"))
		std::cout << "Error loading bar.png" << std::endl;

	_shape.setTexture(&_texture);
	_shape.setPosition(position);
	_shape.setSize({static_cast<float>(_texture.getSize().x), static_cast<float>(_texture.getSize().y)});

	_velocity = 0.0f;
	_isMoving = false;
}

void Bar::MoveLeft(const sf::Time elapsed)
{
	if (abs(_velocity) < MAX_SPEED)
	{
		float increase = SPEED * elapsed.asSeconds();

		if (_velocity > 0)
		{
			increase *= 5;
		}

		_velocity -= increase;
	}

	_isMoving = true;
}

void Bar::MoveRight(const sf::Time elapsed)
{
	if (abs(_velocity) < MAX_SPEED)
	{
		float increase = SPEED * elapsed.asSeconds();

		if (_velocity < 0)
		{
			increase *= 5;
		}

		_velocity += increase;
	}

	_isMoving = true;
}

void Bar::Stop(const sf::RectangleShape& wall)
{
	if (_velocity > 0)
	{
		_shape.move(wall.getPosition().x - _shape.getPosition().x - _shape.getSize().x, 0);
	}
	else
	{
		_shape.move(wall.getPosition().x - _shape.getPosition().x + wall.getSize().x, 0);
	}

	_velocity = 0.0f;
	_isMoving = false;
}

void Bar::Update(const sf::Time elapsed)
{
	if (_velocity != 0.0f)
	{
		_shape.move(_velocity * elapsed.asSeconds(), 0);
		
		if (!_isMoving)
		{
			_velocity += _velocity * - 4.0f * elapsed.asSeconds();

			if (abs(_velocity) < 40.0f)
			{
				_velocity = 0.0f;
			}
		}
	}
}

void Bar::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_shape, states);
}

sf::Vector2f Bar::GetTopMiddlePosition() const
{
	return { _shape.getPosition().x + _shape.getSize().x / 2, _shape.getPosition().y };
}
