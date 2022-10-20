#include "Snake.h"

#include <numbers>

#include "Random.h"

Snake::Snake(const bool useIA)
{
	_body = {};
	_canTakeDamage = true;
	_direction = Direction::RIGHT;
	_canChangeDirection = true;
	_elapsed = sf::milliseconds(0);
	_invincibilityTime = sf::milliseconds(0);
	_useIA = useIA;

	int x = START_X;

	if (useIA)
	{
		x *= 2;
	}

	for (int i = 0; i < START_SIZE; i++)
	{
		sf::CircleShape shape(RADIUS);
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(x - (static_cast<float>(i) * RADIUS * 2.0f), START_Y);
		_body.push_back(shape);
	}
}

sf::Vector2f Snake::getNextPosition(const Direction nextDirection) const
{
	sf::Vector2f nextPosition = _body[0].getPosition();

	if (nextDirection == Direction::UP)
	{
		nextPosition.y -= SPEED;
	}
	else if (nextDirection == Direction::DOWN)
	{
		nextPosition.y += SPEED;
	}
	else if (nextDirection == Direction::LEFT)
	{
		nextPosition.x -= SPEED;
	}
	else if (nextDirection == Direction::RIGHT)
	{
		nextPosition.x += SPEED;
	}

	return nextPosition;
}

void Snake::setBodyColor(int i)
{
	sf::Uint8 alpha = 255;

	if (_invincibilityTime > sf::Time::Zero)
	{
		alpha = static_cast<sf::Uint8>(150 * sin(static_cast<float>(_invincibilityTime.asMilliseconds()) / 500.0f * 2.0f * std::numbers::pi));
	}

	if (i == 0)
	{
		if (_useIA)
		{
			_body[0].setFillColor(sf::Color(255, 70, 70, alpha));
		}
		else
		{
			_body[0].setFillColor(sf::Color(70, 70, 255, alpha));
		}
	}
	else
	{
		if (_useIA)
		{
			_body[i].setFillColor(sf::Color(255 - 155 / _body.size() * (i + 1), 70, 70, alpha));
		}
		else
		{
			_body[i].setFillColor(sf::Color(70, 70, 255 - 155 / _body.size() * (i + 1), alpha));
		}
	}

}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& shape : _body)
	{
		target.draw(shape);
	}
}

void Snake::updateIA(sf::Vector2f eggPosition)
{
	const sf::Vector2f head = _body.front().getPosition();

	if (_invincibilityTime > sf::Time::Zero)
	{
		// If the snake is invincible, confuse the AI by making it move randomly
		eggPosition.x += Random::GetFloat(-300.0f, 300.0f);
		eggPosition.y += Random::GetFloat(-300.0f, 300.0f);
	}

	if ((_direction == Direction::RIGHT && eggPosition.x <= head.x) || (_direction == Direction::LEFT && eggPosition.x >= head.x))
	{
		if (eggPosition.y <= head.y)
		{
			ChangeDirection(Direction::UP);
		}
		else
		{
			ChangeDirection(Direction::DOWN);
		}
	}
	else if ((_direction == Direction::UP && eggPosition.y >= head.y) || (_direction == Direction::DOWN && eggPosition.y <= head.y))
	{
		if (eggPosition.x <= head.x)
		{
			ChangeDirection(Direction::LEFT);
		}
		else
		{
			ChangeDirection(Direction::RIGHT);
		}
	}
}

void Snake::TakeDamage()
{
	_body.pop_back();
	_canTakeDamage = false;
	_invincibilityTime = sf::milliseconds(500);
}

void Snake::ChangeDirection(const Direction direction)
{
	if (_canChangeDirection && direction != _direction)
	{
		_direction = direction;
		_canChangeDirection = false;
	}
}

void Snake::Update(sf::Time elapsed, sf::Vector2f eggPosition)
{
	_elapsed += elapsed;

	if (_invincibilityTime.asMicroseconds() > 0)
	{
		_invincibilityTime -= elapsed;

		if (_invincibilityTime.asMicroseconds() <= 0)
		{
			_invincibilityTime = sf::Time::Zero;
			_canTakeDamage = true;
		}
	}

	while (PLAYER_UPDATE_PER_SECOND <= _elapsed)
	{
		const sf::Vector2f nextPosition = getNextPosition(_direction);
		sf::Uint8 alpha = 255;

		if (_invincibilityTime > sf::Time::Zero)
		{
			alpha = static_cast<sf::Uint8>(150 * sin(static_cast<float>(_invincibilityTime.asMilliseconds()) / 500.0f * 2.0f * std::numbers::pi));
		}

		for (int i = _body.size() - 1; i > 0; i--)
		{
			if (_body[i].getPosition() != _body[i - 1].getPosition())
			{
				_body[i].setPosition(_body[i - 1].getPosition());
			}

			setBodyColor(i);
		}

		setBodyColor(0);

		_body[0].setPosition(nextPosition);
		_canChangeDirection = true;
		_canTakeDamage = true;

		if (_useIA)
		{
			_elapsed -= IA_UPDATE_PER_SECOND;
			updateIA(eggPosition);
		}
		else
		{
			_elapsed -= PLAYER_UPDATE_PER_SECOND;
		}
	}
}

void Snake::Grow()
{
	sf::CircleShape shape(RADIUS);
	shape.setFillColor(sf::Color(70, 70, 255 - 155));
	shape.setPosition(_body.back().getPosition());
	_body.push_back(shape);
}

bool Snake::Hit(const std::vector<sf::Vector2f>& opponentPositions) const
{
	if (_canTakeDamage && _invincibilityTime == sf::Time::Zero)
	{
		for (auto& position : opponentPositions)
		{
			if (_body[0].getPosition() == position)
			{
				return true;
			}
		}

		for (int i = 1; i < static_cast<int>(_body.size()); i++)
		{
			if (_body[0].getPosition() == _body[i].getPosition())
			{
				return true;
			}
		}
	}

	return false;
}

bool Snake::CanEatEgg(const sf::Vector2f& eggPosition) const
{
	return _invincibilityTime == sf::Time::Zero && _body[0].getPosition() == eggPosition;
}

std::vector<sf::Vector2f> Snake::GetPositions() const
{
	std::vector<sf::Vector2f> positions;

	for (auto& shape : _body)
	{
		positions.emplace_back(shape.getPosition());
	}

	return positions;
}
