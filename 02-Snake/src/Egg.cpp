#include "Egg.h"
#include <SFML/Graphics/RenderTarget.hpp>

Egg::Egg()
{
	_shape = sf::CircleShape(5.0f);
	_shape.setFillColor(sf::Color::White);
	_shape.setPosition(300, 400);
}

void Egg::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);
}