#pragma once
#include <SFML/Graphics/CircleShape.hpp>

class Egg final : public sf::Drawable
{
public:
	Egg();

private:
	sf::CircleShape _shape;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	sf::Vector2f GetPosition() const { return _shape.getPosition(); }
	void SetPosition(const sf::Vector2f& position) { _shape.setPosition(position); }
};
