#include "Spark.h"

Spark::Spark(const sf::Vector2f& position, const sf::Vector2f& direction, const sf::Color& color,
	const sf::Time& lifetime)
{
	_shape.setSize({ 5.0f, 5.0f });
	_shape.setPosition(position);
	_shape.setFillColor(color);

	_velocity = direction;
	_lifetime = lifetime;
	_elapsed = sf::Time::Zero;
	_color = color;
}

void Spark::Update(const sf::Time elapsed)
{
	_elapsed += elapsed;
	_shape.move(_velocity * elapsed.asSeconds());
	_shape.setFillColor(sf::Color(_color.r, _color.g, _color.b, 255 - static_cast<sf::Uint8>(_elapsed.asSeconds() / _lifetime.asSeconds() * 255)));
	_shape.rotate(360.0f * elapsed.asSeconds());
}

void Spark::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}
