#pragma once
#include "SFML/Graphics.hpp"

class SecondPainting final : public sf::Drawable
{
public:
	explicit SecondPainting(sf::Vector2u windowSize);

private:
	std::vector<sf::RectangleShape> _shapes;

	static sf::Color getRandomRedColor();
	static sf::Color hsvToRgb(float H, float S, float V);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};