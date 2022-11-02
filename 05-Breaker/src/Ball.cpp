#include "Ball.h"

#include "Assets.h"
#include "Random.h"

Ball::Ball()
{
	const auto& texture = Assets::GetInstance().GetTexture(Asset::BALL);
	_shape.setTexture(&texture);
	_shape.setRadius(static_cast<float>(texture.getSize().x) / 2.0f);
	_shape.setOrigin(_shape.getRadius(), _shape.getRadius());

	_velocity = { 0, 0 };

	_sparks = {};
}

void Ball::moveOutOfBounds(const sf::Shape& bounds, Direction direction)
{
	const sf::FloatRect bound = bounds.getGlobalBounds();

	const float xBound = bounds.getPosition().x;
	const float yBound = bounds.getPosition().y;
	const float widthBound = bound.width;
	const float heightBound = bound.height;

	const float x = _shape.getPosition().x;
	const float y = _shape.getPosition().y;
	const float radius = _shape.getRadius();

	if (direction == Direction::NONE)
	{
		// Check if the ball is colliding with any side of the bounds
		if (bound.contains(getLeftSide(), y))
		{
			direction = Direction::LEFT;
		}
		else if (bound.contains(getRightSide(), y))
		{
			direction = Direction::RIGHT;
		}
		else if (bound.contains(x, getTopSide()))
		{
			direction = Direction::UP;
		}
		else if (bound.contains(x, getBottomSide()))
		{
			direction = Direction::DOWN;
		}
	}

	if (direction == Direction::UP)
	{
		_shape.setPosition(x, yBound + heightBound + radius);
	}
	else if (direction == Direction::DOWN)
	{
		_shape.setPosition(x, yBound - radius);
	}
	else if (direction == Direction::LEFT)
	{
		_shape.setPosition(xBound + widthBound + radius, y);
	}
	else if (direction == Direction::RIGHT)
	{
		_shape.setPosition(xBound - radius, y);
	}
}

void Ball::spawnSparks()
{
	const sf::Vector2f position = _shape.getPosition();
	const float radius = _shape.getRadius();
	constexpr int offset = 5;
	const int size = static_cast<int>(radius / 2) + offset;

	for (int i = -size; i < size; i++)
	{
		for (int j = -size; j < size; j++)
		{
			// Ignore sparks outside the circle + offset
			if (abs(i * i + j * j) > radius * radius + offset * offset)
			{
				continue;
			}

			auto color = sf::Color(199, 67, 47);

			// Make the sparks a different color if they are on the edge of the circle and in the direction of the velocity
			if (abs(i * i + j * j) > (radius - offset) * (radius - offset) || (i * _velocity.x < 0 && j * _velocity.y < 0))
			{
				if (i * _velocity.x > 0 || j * _velocity.y > 0)
				{
					color = sf::Color(206, 86, 42);
				}
			}

			auto sparkPosition = sf::Vector2f(position.x + i, position.y + j);

			_sparks.emplace_back(Spark(
				sparkPosition,
				(position - sparkPosition) * Random::GetFloat(1.0f, 6.0f),
				color,
				sf::Time(sf::seconds(Random::GetFloat(0.05f, 0.125f)))
			));
		}
	}
}

void Ball::onBounce(const sf::Shape& shape)
{
	spawnSparks();

	// Increase the speed of the ball every hit
	if (abs(_velocity.y) < MAX_Y_VELOCITY)
	{
		_velocity.y += _velocity.y > 0 ? 3.0f : -3.0f;
	}
}

void Ball::Update(const sf::Time elapsed)
{
	_shape.move(_velocity * elapsed.asSeconds());

	_sparkCooldown -= elapsed;

	if (IsMoving() && _sparkCooldown <= sf::Time::Zero)
	{
		// Draw sparks on all pixels around the ball
		spawnSparks();

		_sparkCooldown += SPARK_COOLDOWN;
	}

	for (auto& spark : _sparks)
	{
		spark.Update(elapsed);
	}

	_sparks.erase(
		std::remove_if(
			_sparks.begin(),
			_sparks.end(),
			[](const Spark& spark) { return !spark.IsAlive(); }
		),
		_sparks.end()
	);
}

bool Ball::IsColliding(const sf::Shape& bounds) const
{
	return _shape.getGlobalBounds().intersects(bounds.getGlobalBounds());
}


void Ball::Bounce(const sf::Shape& bounds, Direction direction)
{
	const sf::FloatRect bound = bounds.getGlobalBounds();

	const float x = _shape.getPosition().x;
	const float y = _shape.getPosition().y;

	if (direction == Direction::NONE)
	{
		if (bound.contains(getLeftSide(), y))
		{
			direction = Direction::LEFT;
		}
		else if (bound.contains(getRightSide(), y))
		{
			direction = Direction::RIGHT;
		}
		else if (bound.contains(x, getTopSide()))
		{
			direction = Direction::UP;
		}
		else if (bound.contains(x, getBottomSide()))
		{
			direction = Direction::DOWN;
		}
	}

	// Bounce the ball off the bounds
	if (direction == Direction::LEFT || direction == Direction::RIGHT)
	{
		_velocity.x = -_velocity.x;
	}
	else if (direction == Direction::UP || direction == Direction::DOWN)
	{
		_velocity.y = -_velocity.y;
	}

	moveOutOfBounds(bounds, direction);
	onBounce(bounds);
}

void Ball::Bounce(Bar& bar)
{
	// Increase the velocity of the ball depending on where it hits the bar
	const float barCenter = bar.GetBar().getPosition().x + bar.GetBar().getSize().x / 2;
	const float diff = (_shape.getPosition().x - barCenter) / (bar.GetBar().getSize().x / 2);

	_velocity.x += diff * (abs(_velocity.x * 1.5f) + 20.0f) + bar.GetVelocity() / 10.0f;

	if (abs(_velocity.x) > MAX_X_VELOCITY)
	{
		_velocity.x = MAX_X_VELOCITY * (_velocity.x / abs(_velocity.x));
	}

	// Always bounce the ball upwards
	_velocity.y = -std::abs(_velocity.y);

	moveOutOfBounds(bar.GetBar());
	onBounce(bar.GetBar());
}

void Ball::Launch(const sf::Vector2f& direction)
{
	_velocity = direction;
}

void Ball::Reset()
{
	_velocity = { 0, 0 };
}

void Ball::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& spark : _sparks)
	{
		target.draw(spark, states);
	}
	
	target.draw(_shape, states);
}
