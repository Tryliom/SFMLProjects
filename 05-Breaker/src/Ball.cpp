#include "Ball.h"

Ball::Ball()
{
	_texture.loadFromFile("data/textures/ball.png");
	_shape.setRadius(static_cast<float>(_texture.getSize().x) / 2.0f);
	_shape.setOrigin(_shape.getRadius(), _shape.getRadius());

	_velocity = { 0, 0 };
}

void Ball::moveOutOfBounds(const sf::Shape& bounds)
{
	const sf::FloatRect bound = bounds.getGlobalBounds();

	const float xBound = bounds.getPosition().x;
	const float yBound = bounds.getPosition().y;
	const float widthBound = bound.width;
	const float heightBound = bound.height;

	const float x = _shape.getPosition().x;
	const float y = _shape.getPosition().y;
	const float radius = _shape.getRadius();

	// Check if the ball is colliding with any side of the bounds
	if (bound.contains(getLeftSide(), y))
	{
		// Move the ball to the edge of the bounds
		_shape.setPosition(xBound + widthBound + radius, y);
	}
	else if (bound.contains(getRightSide(), y))
	{
		// Move the ball to the edge of the bounds
		_shape.setPosition(xBound - radius, y);
	}
	else if (bound.contains(x, getTopSide()))
	{
		// Move the ball to the edge of the bounds
		_shape.setPosition(x, yBound + heightBound + radius);
	}
	else if (bound.contains(x, getBottomSide()))
	{
		// Move the ball to the edge of the bounds
		_shape.setPosition(x, yBound - radius);
	}
}

void Ball::Update(const sf::Time elapsed)
{
	_shape.move(_velocity * elapsed.asSeconds());
	_shape.setTexture(&_texture);
}

bool Ball::IsColliding(const sf::Shape& bounds) const
{
	return _shape.getGlobalBounds().intersects(bounds.getGlobalBounds());
}


void Ball::Bounce(const sf::Shape& bounds)
{
	const sf::FloatRect bound = bounds.getGlobalBounds();

	const float xBound = bounds.getPosition().x;
	const float yBound = bounds.getPosition().y;
	const float widthBound = bound.width;
	const float heightBound = bound.height;

	const float x = _shape.getPosition().x;
	const float y = _shape.getPosition().y;
	const float radius = _shape.getRadius();

	// Check if the ball is colliding with any side of the bounds
	if (bound.contains(getLeftSide(), y))
	{
		// Left side
		_velocity.x = abs(_velocity.x);
	}
	else if (bound.contains(getRightSide(), y))
	{
		// Right side
		_velocity.x = abs(_velocity.x) * -1;
	}
	else if (bound.contains(x, getTopSide()))
	{
		// Top side
		_velocity.y = abs(_velocity.y);
	}
	else if (bound.contains(x, getBottomSide()))
	{
		// Bottom side
		_velocity.y = abs(_velocity.y) * -1;
	}

	moveOutOfBounds(bounds);
}

void Ball::Bounce(const Bar& bar)
{
	// Increase the velocity of the ball depending on where it hits the bar
	const float barCenter = bar.GetBar().getPosition().x + bar.GetBar().getSize().x / 2;
	const float diff = (_shape.getPosition().x - barCenter) / (bar.GetBar().getSize().x / 2);

	_velocity.x += diff * (abs(_velocity.x * 1.5f) + 5.0f) + bar.GetVelocity() / 10.0f;

	// Always bounce vertically only if the ball hit the bar vertically
	if (_shape.getPosition().y < bar.GetBar().getPosition().y)
	{
		_velocity.y = -std::abs(_velocity.y);

		// Increase the speed of the ball every hit
		_velocity.y *= 1.05f;
	}

	moveOutOfBounds(bar.GetBar());
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
	target.draw(_shape, states);

	sf::CircleShape shadow;
	shadow.setRadius(_shape.getRadius());
	shadow.setOrigin(_shape.getRadius(), _shape.getRadius());
	shadow.setPosition(_shape.getPosition().x + 3, _shape.getPosition().y + 3);
	shadow.setFillColor(sf::Color(0, 0, 0, 100));

	target.draw(shadow, states);
}
