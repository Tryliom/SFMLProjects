#pragma once
#include "SFML/Graphics.hpp"

class FirstPainting : public sf::Drawable
{
public:
	FirstPainting(sf::Vector2u windowSize);

private:
	std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> _shapes;

	void addShape(sf::RectangleShape& shape, sf::Vector2u windowSize);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};