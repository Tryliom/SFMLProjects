#pragma once
#include "SFML/Graphics.hpp"

class Spark final: public sf::Drawable
{
public:
	Spark(const sf::Vector2f& position, const sf::Vector2f& direction, const sf::Color& color, const sf::Time& lifetime);

private:
	sf::RectangleShape _shape;
	sf::Vector2f _velocity;
	sf::Time _lifetime;
	sf::Time _elapsed;
	sf::Color _color;

public:
	bool IsAlive() const { return _elapsed < _lifetime; }

	void Update(const sf::Time elapsed);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};