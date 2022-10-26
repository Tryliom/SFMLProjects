#include "Ball.h"

Ball::Ball()
{
	_shape.setRadius(8);
	_shape.setFillColor(sf::Color::Blue);
	_shape.setOrigin(_shape.getRadius(), _shape.getRadius());

	_velocity = { 0, 0 };
}

void Ball::Update(const sf::Time elapsed)
{
	_shape.move(_velocity * elapsed.asSeconds());
}

bool Ball::IsColliding(const sf::Shape& bounds) const
{
	return _shape.getGlobalBounds().intersects(bounds.getGlobalBounds());
}


void Ball::Bounce(const sf::Shape& bounds)
{
	// Check if the ball is colliding with any side of the bounds
	if (_shape.getPosition().x < bounds.getPosition().x)
	{
		// Left side
		_velocity.x = -_velocity.x;
	}
	else if (_shape.getPosition().x + _shape.getRadius() * 2 > bounds.getPosition().x + bounds.getGlobalBounds().width)
	{
		// Right side
		_velocity.x = -_velocity.x;
	}
	else if (_shape.getPosition().y < bounds.getPosition().y)
	{
		// Top side
		_velocity.y = -_velocity.y;
	}
	else if (_shape.getPosition().y + _shape.getRadius() * 2 > bounds.getPosition().y + bounds.getGlobalBounds().height)
	{
		// Bottom side
		_velocity.y = -_velocity.y;
	}
}

void Ball::Bounce(const Bar& bar)
{
	// Increase the velocity of the ball depending on where it hits the bar
	const float barCenter = bar.GetBar().getPosition().x + bar.GetBar().getSize().x / 2;
	const float diff = (_shape.getPosition().x - barCenter) / (bar.GetBar().getSize().x / 2);

	_velocity.x += diff * abs(_velocity.x * 1.5f) + bar.GetVelocity() / 10.0f;

	// Always bounce vertically only if the ball hit the bar vertically
	if (_shape.getPosition().y < bar.GetBar().getPosition().y)
	{
		_velocity.y = -std::abs(_velocity.y);

		// Increase the speed of the ball every hit
		_velocity *= 1.02f;
	}
}

void Ball::Launch(const sf::Vector2f& direction)
{
	_velocity = direction;
}

void Ball::Reset()
{
	_velocity = { 0, 0 };
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}
