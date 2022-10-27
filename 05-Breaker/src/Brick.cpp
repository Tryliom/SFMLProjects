#include "Brick.h"
#include "Random.h"

Brick::Brick(const sf::Vector2f& position)
{
	_shape.setSize({ BRICK_WIDTH, BRICK_HEIGHT });
	_shape.setPosition(position);
	_shape.setFillColor(sf::Color(Random::GetInt(0, 255), Random::GetInt(0, 255), Random::GetInt(0, 255)));
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(-2.0f);

	_isDestroyed = false;
}

void Brick::Break()
{
	_isDestroyed = true;
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}
