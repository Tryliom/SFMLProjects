#include "ShapeAnimation.h"

ShapeAnimation::ShapeAnimation(const sf::RectangleShape& shape, sf::Time lifeTime)
	: Animation(lifeTime, shape.getPosition())
{
	_shape = shape;
}

void ShapeAnimation::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_shape, states);
}

void ShapeAnimation::Update(sf::Time elapsed)
{
	Animation::Update(elapsed);

	sf::Color color = _shape.getFillColor();
	color.a = static_cast<sf::Uint8>(255 - (255 * _elapsed.asSeconds() / _lifeTime.asSeconds()));
	_shape.setFillColor(color);

	sf::Color outlineColor = _shape.getOutlineColor();
	outlineColor.a = static_cast<sf::Uint8>(255 - (255 * _elapsed.asSeconds() / _lifeTime.asSeconds()));
	_shape.setOutlineColor(outlineColor);
}
