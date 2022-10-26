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
		_velocity -= SPEED * elapsed.asSeconds();
	}

	_isMoving = true;
}

void Bar::MoveRight(const sf::Time elapsed)
{
	if (abs(_velocity) < MAX_SPEED)
	{
		_velocity += SPEED * elapsed.asSeconds();
	}

	_isMoving = true;
}

void Bar::Update(const sf::Time elapsed)
{
	if (_velocity != 0.0f)
	{
		_shape.move(_velocity * elapsed.asSeconds(), 0);
		
		if (!_isMoving)
		{
			_velocity += _velocity * - 2.0f * elapsed.asSeconds();

			if (abs(_velocity) < 1.0f)
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
